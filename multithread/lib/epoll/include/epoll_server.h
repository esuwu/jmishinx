//
// Created by kira on 4/14/20.
//

#ifndef PROJECT_LIB_EPOLL_SRC_SERVER_H_
#define PROJECT_LIB_EPOLL_SRC_SERVER_H_

#include "file_descriptor.h"
#include "tcp_connection.h"
#include "epoll_base.h"

#include <string>

namespace epoll {
class Server {
 public:
    Server(const std::string &ip, uint16_t port, ClientCallback on_read,
           ClientCallback on_write = [](tcp::Connection &conn) {},
           size_t num_threads = std::thread::hardware_concurrency());

    void spin_once();
    void spin();

    [[nodiscard]] bool is_opened() const;
    [[nodiscard]] std::string const &addr() const;
    [[nodiscard]] uint16_t port() const;
 private:
    void open(const std::string &ip, uint16_t port);
    void set_max_connections(uint32_t max_connections);

    file_descriptor::FileDescriptor _server_fd;
    Epoll _epoll{};

    std::string _addr;
    uint16_t _port = 0;
};
}  // namespace epoll


#endif //PROJECT_LIB_EPOLL_SRC_SERVER_H_
