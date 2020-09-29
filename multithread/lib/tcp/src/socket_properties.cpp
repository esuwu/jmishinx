//
// Created by kira on 28.09.2020.
//

#include "socket_properties.h"

#include <utility>

tcp::Properties::Properties(std::string dst_addr,
                            std::string src_addr,
                            uint16_t dst_port,
                            uint16_t src_port)
    : _dst_addr(std::move(dst_addr)),
      _src_addr(std::move(src_addr)),
      _dst_port(dst_port),
      _src_port(src_port) {}
std::string const &tcp::Properties::dst_addr() const {
    return _dst_addr;
}
std::string const &tcp::Properties::src_addr() const {
    return _src_addr;
}
uint16_t tcp::Properties::dst_port() const {
    return _dst_port;
}
uint16_t tcp::Properties::src_port() const {
    return _src_port;
}
