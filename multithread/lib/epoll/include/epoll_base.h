//
// Created by kira on 4/14/20.
//

#ifndef PROJECT_LIB_EPOLL_INCLUDE_EPOLL_BASE_H_
#define PROJECT_LIB_EPOLL_INCLUDE_EPOLL_BASE_H_

#include "file_descriptor.h"
#include "tcp_connection.h"
#include "thread_poll.h"

#include <functional>
#include <unordered_map>

namespace epoll {
using ClientCallback = std::function<void(tcp::Connection &)>;

class Epoll {
 public:
    Epoll() = default;
    Epoll(ClientCallback on_read,
          ClientCallback on_write,
          const file_descriptor::FileDescriptor &server_fd);

    Epoll(Epoll &&other) noexcept = default;
    Epoll &operator=(Epoll &&other) noexcept = default;

    void add(const tcp::Connection &connection, uint32_t events);
    void mod(const tcp::Connection &connection, uint32_t events);
    void del(const tcp::Connection &connection);

    void spin_once();

 private:
    void ctl(int fd, uint32_t events, int operation);
    void accept();
    void handle_client(int clinet_fd, unsigned event);

    file_descriptor::FileDescriptor _epoll_fd;
    int _server_fd{-1};

    ClientCallback _on_read;
    ClientCallback _on_write;

    std::unordered_map<int, tcp::Connection> _connections;
    thread_poll::ThreadPoll _thread_poll{};
};
}  // namespace epoll


#endif //PROJECT_LIB_EPOLL_INCLUDE_EPOLL_BASE_H_
