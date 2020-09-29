//
// Created by kira on 30.09.2020.
//

//
// Created by kira on 30.09.2020.
//

#include "http_request.h"

#include <iostream>
#include <chrono>
#include <base_exception.h>

using namespace std::chrono_literals;

int main() {
    http::Request http_request{
        "GET / HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/85.0.4183.121 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n"
        "Purpose: prefetch\r\n"
        "Sec-Fetch-Site: none\r\n"
        "Sec-Fetch-Mode: navigate\r\n"
        "Sec-Fetch-User: ?1\r\n"
        "Sec-Fetch-Dest: document\r\n"
        "Accept-Encoding: gzip, deflate, br\r\n"
        "Accept-Language: ru-RU,ru;q=0.9,en-US;q=0.8,en;q=0.7\r\n\r\n"
    };
    std::cout << http_request.method() << std::endl;
    std::cout << http_request.path() << std::endl;
    std::cout << http_request.version() << std::endl;
    return 0;
}
