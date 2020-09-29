//
// Created by kira on 28.09.2020.
//

#include "tcp_server.h"

#include <iostream>

int main() {
    tcp::Server server{"0.0.0.0", 12222};
    auto connection = server.accept();
    std::string hello(5, 0);
    std::string bye{"bye"};
    while (true) {
        if (connection.is_opened()) {
            connection >> hello;
        } else {
            break;
        }
        if (connection.is_opened()) {
            connection << bye;
        } else {
            break;
        }
        std::cout << hello << std::endl;
    }
    return 0;
}
