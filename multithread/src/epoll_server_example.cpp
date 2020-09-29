//
// Created by kira on 4/15/20.
//

#include "epoll_server.h"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    auto on_read = [](tcp::Connection &conn) {
        std::string to_read;
        conn >> to_read;
        std::cout << "reading from " << conn.props().dst_addr() << std::endl;
        std::cout << to_read << std::endl;

        std::string to_write("MUDAMUDAMUDA");
//        std::this_thread::sleep_for(10s);
        conn << to_write;
        std::cout << "writing to " << conn.props().dst_addr() << std::endl;
    };

    epoll::Server server("0.0.0.0", 8080, on_read);
    server.spin();
    return 0;
}
