//
// Created by kira on 28.09.2020.
//

#include "tcp_connection.h"

#include <iostream>

int main() {
    tcp::Connection connection{"0.0.0.0", 12222};
    std::string hello{"hello"};
    std::string bye(3, 0);
    connection << hello;
    connection >> bye;
    std::cout << bye << std::endl;
    return 0;
}
