//
// Created by kira on 30.09.2020.
//

#include "epoll_server.h"
#include "http_request.h"

#include <iostream>
#include <chrono>
#include <base_exception.h>

using namespace std::chrono_literals;

int main() {
    auto on_read = [](tcp::Connection &conn) {
        std::string request_string{};
        conn >> request_string;
        std::cout << "reading from " << conn.props().dst_addr() << std::endl;
        std::cout << request_string << std::endl;

        http::Request http_request{request_string};

        std::string response_string{
            "HTTP/1.1 200 OK\r\n"
            "Server: YarServer/2009-09-09\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 9876\r\n"
            "Connection: keep-alive\r\n\r\n"
            "<html><body><h1>"
            "I got method: " + http_request.method() + "\t" +
            "With path: " + http_request.path() +
            "</h1></body></html>"};

        conn << response_string;
    };

    epoll::Server server("0.0.0.0", 8081, on_read);
    try {
        server.spin();
    } catch (base_exception::Exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
