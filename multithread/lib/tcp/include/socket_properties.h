//
// Created by kira on 28.09.2020.
//

#ifndef CPP_CPP_MULTITHREAD_LIB_SOCKET_INCLUDE_SOCKET_PROPERTIES_H_
#define CPP_CPP_MULTITHREAD_LIB_SOCKET_INCLUDE_SOCKET_PROPERTIES_H_

#include <string>

namespace tcp {
class Properties {
 public:
    Properties(std::string dst_addr = {},
               std::string src_addr = {},
               uint16_t dst_port = {},
               uint16_t src_port = {});

    [[nodiscard]] std::string const &dst_addr() const;
    [[nodiscard]] std::string const &src_addr() const;
    [[nodiscard]] uint16_t dst_port() const;
    [[nodiscard]] uint16_t src_port() const;

 private:
    std::string _dst_addr;
    std::string _src_addr;
    uint16_t _dst_port;
    uint16_t _src_port;
};
}  // namespace socket

#endif //CPP_CPP_MULTITHREAD_LIB_SOCKET_INCLUDE_SOCKET_PROPERTIES_H_
