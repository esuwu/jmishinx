//
// Created by kira on 3/31/20.
//

#include "tcp_connection.h"
#include "base_exception.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <utility>

using base_exception::Exception;
using file_descriptor::FileDescriptor;

namespace tcp {
Connection::Connection(file_descriptor::FileDescriptor fd) {
    sockaddr_in client_address{};
    socklen_t client_address_size = sizeof(client_address);
    if (getsockname(fd,
                    reinterpret_cast<sockaddr *>(&client_address),
                    &client_address_size) == -1) {
        throw Exception("client info error");
    }

    _fd = std::move(fd);
    _properties = Properties{
        inet_ntoa(client_address.sin_addr),
        {},  // TODO
        ntohs(client_address.sin_port),
        {}  // TODO
    };
}

Connection::Connection(FileDescriptor fd, Properties properties)
    : _fd(std::move(fd)),
      _properties(std::move(properties)) {}

Connection::Connection(std::string ip, uint16_t port) {
    FileDescriptor sock(socket(AF_INET, SOCK_STREAM, 0));
    if (sock == -1) {
        throw Exception("socket creation failed");
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (::connect(sock,
                  reinterpret_cast<sockaddr *>(&addr),
                  sizeof(addr)) == -1) {
        throw Exception("connection failed");
    }

    sockaddr_in client_address{};
    socklen_t client_address_size = sizeof(client_address);
    if (getsockname(sock,
                    reinterpret_cast<sockaddr *>(&client_address),
                    &client_address_size) == -1) {
        throw Exception("client info error");
    }

    _fd = std::move(sock);
    _properties = Properties{
        std::move(ip),
        inet_ntoa(client_address.sin_addr),
        port,
        ntohs(client_address.sin_port)
    };
}

size_t Connection::write(const void *data, size_t size) {
    ssize_t written = send(_fd, data, size, 0);
    if (written == -1) {
        throw Exception("write error");
    }
    if (written == 0) {
        _fd.close();
    }
    return written;
}

void Connection::write_exact(const void *data, size_t size) {
    size_t written = 0;
    while (size != written and is_opened()) {
        written += write(static_cast<const char *>(data) + written, size - written);
    }
}

Connection &Connection::operator<<(const std::string &data) {
    write_exact(data.c_str(), data.length());
    return *this;
}

size_t Connection::read(void *data, size_t size) {
    ssize_t read_n = ::recv(_fd, data, size, 0);
    if (read_n == -1) {
        throw Exception("read error");
    }
    if (read_n == 0) {
        _fd.close();
    }
    return read_n;
}
void Connection::read_exact(void *data, size_t size) {
    size_t read_n = 0;
    while (size != read_n and is_opened()) {
        read_n += read(static_cast<char *>(data) + read_n, size - read_n);
    }
}

Connection &Connection::operator>>(std::string &data) {
    constexpr size_t BATCHSIZE = 1024;
    data.resize(1024);
    data.resize(read(data.data(), BATCHSIZE));
    return *this;
}

void Connection::set_timeout(std::chrono::seconds seconds, std::chrono::microseconds microseconds) {
    timeval _timeout{.tv_sec = seconds.count(), .tv_usec = microseconds.count()};
    if (setsockopt(_fd,
                   SOL_SOCKET,
                   SO_SNDTIMEO,
                   &_timeout,
                   sizeof(_timeout)) == -1) {
        throw Exception("timeout set failed");
    }
    if (setsockopt(_fd,
                   SOL_SOCKET,
                   SO_RCVTIMEO,
                   &_timeout,
                   sizeof(_timeout)) == -1) {
        throw Exception("timeout set failed");
    }
}
bool Connection::is_opened() const {
    return _fd != -1;
}
const Properties &Connection::props() const {
    return _properties;
}
bool Connection::is_blocking() const {
    int val = fcntl(_fd, F_GETFL, 0);
    if (val < 0) {
        throw Exception("check blocking");
    }
    return !(val & O_NONBLOCK);
}
const file_descriptor::FileDescriptor &Connection::fd() const {
    return _fd;
}
}  // namespace tcp
