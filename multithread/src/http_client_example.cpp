//
// Created by alexandr on 29.09.2020.
//

#include "tcp_connection.h"
#include <iostream>

int main() {
    std::string http_request_example_GET = "GET /static/index.html HTTP/1.1\nHost: localhost:8080\r\n\r\n"
    std::string http_request_example_HEAD = "HEAD /static/index.html HTTP/1.1\nHost: localhost:8080\r\n\r\n"
    tcp::Connection connection("0.0.0.0", 8080);
    try {
        std::string to_write{"ORA"};
        connection << to_write;

        to_write = "ORAORA";
        connection << http_request_example;

        std::string to_read;
        connection >> to_read;
        std::cout << to_read << std::endl;

    } catch (std::exception & e) {
        e.what();
    }

    return 0;
}

