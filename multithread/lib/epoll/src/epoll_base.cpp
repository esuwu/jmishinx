//
// Created by kira on 4/14/20.
//

#include "base_exception.h"
#include "epoll_base.h"

#include <sys/epoll.h>
#include <netinet/in.h>
#include <utility>

using base_exception::Exception;
using file_descriptor::FileDescriptor;

namespace epoll {
const size_t QUEUE_SIZE = 128;

Epoll::Epoll(ClientCallback on_read,
             ClientCallback on_write,
             const file_descriptor::FileDescriptor &server_fd)
    : _on_read(std::move(on_read)),
      _on_write(std::move(on_write)),
      _epoll_fd(epoll_create(0xD1C)) {

    if (_epoll_fd == -1) {
        throw Exception("epoll creation failed");
    }

    ctl(server_fd, EPOLLIN, EPOLL_CTL_ADD);
    _server_fd = server_fd;
}

void Epoll::add(tcp::Connection const &connection, uint32_t events) {
    ctl(connection.fd(), events, EPOLL_CTL_ADD);
}

void Epoll::mod(tcp::Connection const &connection, uint32_t events) {
    ctl(connection.fd(), events, EPOLL_CTL_MOD);
}

void Epoll::del(tcp::Connection const &connection) {
    ctl(connection.fd(), 0, EPOLL_CTL_DEL);
}

void Epoll::ctl(int fd, uint32_t events, int operation) {
    epoll_event event{};
    event.data.fd = fd;
    event.events = events;
    if (epoll_ctl(_epoll_fd.fd(), operation, fd, &event) == -1) {
        throw Exception("epoll_ctl error on operation: " + std::to_string(operation));
    }
}

void Epoll::spin_once() {
    if (_server_fd == -1) {
        throw Exception("polling events w/o server");
    }
    std::vector<epoll_event> epoll_events(QUEUE_SIZE);
    int nfds = epoll_wait(_epoll_fd, epoll_events.data(), QUEUE_SIZE, -1);
    if (nfds == -1) {
        if (errno == EINTR) {
            spin_once();
            return;
        }
        throw Exception("epoll_wait failed");
    }
    for (epoll_event &event : epoll_events) {
        int fd = event.data.fd;
        uint32_t events = event.events;
        if (fd == _server_fd) {
            accept();
        } else {
            handle_client(fd, events);
        }
    }
}

void Epoll::accept() {
    int client_fd = ::accept(_server_fd, nullptr, nullptr);
    if (client_fd == -1) {
        throw Exception("accept error");
    }
    _connections[client_fd] = tcp::Connection(FileDescriptor(client_fd));
    add(_connections[client_fd], EPOLLIN | EPOLLOUT | EPOLLET);
}

void Epoll::handle_client(int client_fd, unsigned event) {
    tcp::Connection &connection = _connections[client_fd];
    if (event & EPOLLHUP || event & EPOLLERR || !connection.is_opened()) {
        _connections.erase(client_fd);
        return;
    }
    if (event & EPOLLIN) {
        _thread_poll.q().push([this, &connection] {_on_read(connection);});
    }
    if (event & EPOLLOUT) {
        _thread_poll.q().push([this, &connection] {_on_write(connection);});
    }
}
}  // namespace epoll
