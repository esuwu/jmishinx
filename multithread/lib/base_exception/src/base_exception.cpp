//
// Created by kira on 3/23/20.
//

#include <cstring>
#include "base_exception.h"


namespace base_exception {
Exception::Exception(std::string es) : _errstr(std::move(es)) {
    _errstr += "\n";
    _errstr += strerror(errno);
}

const char *Exception::what() const noexcept {
    return _errstr.c_str();
}
}  // namespace base_exception
