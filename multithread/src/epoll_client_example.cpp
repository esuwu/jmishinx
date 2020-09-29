//
// Created by kira on 4/15/20.
//

#include "tcp_connection.h"
#include <iostream>

int main() {
    tcp::Connection connection("0.0.0.0", 8080);
    try {
        std::string to_write{"ORA"};
        connection << to_write;

        to_write = "ORAORA";
        connection << to_write;

        std::string to_read;
        connection >> to_read;
        std::cout << to_read << std::endl;

    } catch (std::exception & e) {
        e.what();
    }

    return 0;
}

