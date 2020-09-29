//
// Created by kira on 29.09.2020.
//

#ifndef CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_RESPONSE_H_
#define CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_RESPONSE_H_

#include <string>

namespace http {


constexpr const char *end_of_line = "\r\n\r\n";
constexpr const char *end_of_file = "\r\n";
constexpr const char *root_directory = "static/";
constexpr const char *server_name = "jmishinx: ";

namespace connection {
constexpr const char *C_Close = "close";
constexpr const char *C_KeepAlive = "keep-alive";
}

namespace method {
constexpr const char *M_GET = "GET";
constexpr const char *M_HEAD = "GET";
}

namespace status {
constexpr const char *S_200_OK = "200 OK";
constexpr const char *S_404_OK = "404 Not Found";
constexpr const char *S_403_OK = "200 Forbidden";
}

namespace mime_type {
constexpr const char *MT_HTML = "text/html";
constexpr const char *MT_PLAIN = "text/plain";
constexpr const char *MT_CSS = "text/css";
constexpr const char *MT_GIF = "image/gif";
constexpr const char *MT_PNG = "image/png";
constexpr const char *MT_JPG = "image/jpeg";
constexpr const char *MT_TIFF = "image/tiff";
constexpr const char *MT_BMP = "image/bmp";
constexpr const char *MT_JS = "application/javascript";
constexpr const char *MT_SWF = "application/x-shockwave-flash";
const char * determine_content_type(const std::string& file_path);
}

class HttpResponse {
 public:
  HttpResponse(const std::string &method, const std::string &filename);
  std::string build_response();

 private:
  std::string get_date();
  std::string _method;
  std::string _filepath;
};
}  // namespace http

#endif //CPP_MULTITHREAD_LIB_HTTP_INCLUDE_HTTP_RESPONSE_H_
