//
// Created by kira on 29.09.2020.
//

#include "http_request.h"

#include <regex>

namespace http {
enum Parsed: int {Method = 1, Path, Version};
Request::Request(const std::string &request) {
    std::regex http_regex{R"((GET|HEAD) (.+) (HTTP\/\d+.\d+)\r\n(?:.+: .+\r\n)+)"};
    std::smatch match_results;
    std::regex_search(request, match_results, http_regex);

    _method = match_results[Parsed::Method];
    _path = match_results[Parsed::Path];
    _version = match_results[Parsed::Version];
}
const std::string &Request::method() const {
    return _method;
}
const std::string &Request::path() const {
    return _path;
}
const std::string &Request::version() const {
    return _version;
}
const Headers &Request::headers() const {
    return _headers;
}
}  // namespace http
