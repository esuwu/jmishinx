//
// Created by kira on 29.09.2020.
//

#ifndef CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_REQUEST_H_
#define CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_REQUEST_H_

#include <iostream>
#include <unordered_map>

namespace http {
using Headers = std::unordered_map<std::string, std::string>;
class Request {
 public:
    explicit Request(const std::string &request);

    const std::string &method() const;
    const std::string &path() const;
    const std::string &version() const;
    const Headers &headers() const;

 private:
    std::string _method;
    std::string _path;
    std::string _version;
    Headers _headers;
};


}  // namespace http

#endif //CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_REQUEST_H_
