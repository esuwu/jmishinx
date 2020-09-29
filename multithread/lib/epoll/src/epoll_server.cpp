//
// Created by kira on 4/14/20.
//

#include "epoll_server.h"
#include "base_exception.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <utility>

using base_exception::Exception;
using file_descriptor::FileDescriptor;

namespace epoll {
Server::Server(const std::string &ip,
               uint16_t port,
               ClientCallback on_read,
               ClientCallback on_write) {
    open(ip, port);
    _epoll = Epoll(std::move(on_read), std::move(on_write), _server_fd);
}

void Server::open(const std::string &ip, uint16_t port) {
    FileDescriptor listener{socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP)};
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

    _addr = ip;
    _port = port;
    _server_fd = std::move(listener);

    set_max_connections(1024);
}

void Server::set_max_connections(uint32_t max_connections) {
    if (listen(_server_fd.fd(), max_connections) == -1) {
        _server_fd.close();
        throw Exception("listen error");
    }
}

void Server::spin_once() {
    _epoll.spin_once();
}

void Server::spin() {
    while (is_opened()) {
        spin_once();
    }
}

bool Server::is_opened() const {
    return _server_fd != -1;
}

std::string const &Server::addr() const {
    return _addr;
}

uint16_t Server::port() const {
    return _port;
}
}  // namespace epoll
