//
// Created by kira on 3/31/20.
//

#include "tcp_server.h"
#include "base_exception.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using base_exception::Exception;
using file_descriptor::FileDescriptor;

namespace tcp {
Server::Server(std::string ip, uint16_t port, size_t max_connections) {
    FileDescriptor listener{socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)};
    if (listener == -1) {
        throw Exception("socket creation failed");
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    if (bind(listener,
             reinterpret_cast<sockaddr *>(&addr),
             sizeof(addr)) == -1) {
        throw Exception("bind failed");
    }

    _addr = std::move(ip);
    _port = port;
    _fd = std::move(listener);

    set_max_connections(max_connections);
}

Connection Server::accept() {
    sockaddr_in client_address{};
    int client_address_size = sizeof(client_address);
    FileDescriptor sock{::accept(_fd,
                                 reinterpret_cast<sockaddr *>(&client_address),
                                 reinterpret_cast<socklen_t *>(&client_address_size))};
    if (sock == -1) {
        throw Exception("accept error");
    }
    return Connection(std::move(sock),
                      Properties{inet_ntoa(client_address.sin_addr), _addr,
                                 ntohs(client_address.sin_port), _port});
}

void Server::set_max_connections(int max_connections) {
    if (listen(_fd.fd(), max_connections) == -1) {
        _fd.close();
        throw Exception("listen error");
    }
}

bool Server::is_opened() const {
    return _fd != -1;
}

std::string const &Server::addr() const {
    return _addr;
}

uint16_t Server::port() const {
    return _port;
}
}  // namespace tcp
