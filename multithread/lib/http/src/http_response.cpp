//
// Created by kira on 29.09.2020.
//

#include "http_response.h"
#include <fstream>
#include <time.h>

namespace http{

 const char * mime_type::determine_content_type(const std::string& file_path) {
    if (file_path.ends_with("html") || file_path.ends_with("htm")) {
        return mime_type::MT_HTML;
    }
    else if (file_path.ends_with("css")) {
        return mime_type::MT_CSS;
    }
    else if (file_path.ends_with("gif")) {
        return mime_type::MT_GIF;
    }
    else if (file_path.ends_with("png")) {
        return mime_type::MT_PNG;
    }
    else if (file_path.ends_with("jpg") || file_path.ends_with("jpe") || file_path.ends_with("jpeg")) {
        return mime_type::MT_JPG;
    }
    else if (file_path.ends_with("tiff") || file_path.ends_with("tif")) {
        return mime_type::MT_TIFF;
    }
    else if (file_path.ends_with("bmp")) {
        return mime_type::MT_BMP;
    }
    else if (file_path.ends_with("js")) {
        return mime_type::MT_JS;
    }
    else if (file_path.ends_with("swf")) {
        return mime_type::MT_SWF;
    }
    return mime_type::MT_PLAIN;
}

HttpResponse::HttpResponse(const std::string& method, const std::string& filename) {
    bool have_root_directory_substr;
    size_t pos = filename.find(root_directory);
    if (pos != std::string::npos)
        have_root_directory_substr = true;
    else {
        have_root_directory_substr = false;
    }

    _filepath = have_root_directory_substr ? filename : root_directory + filename;

}

std::string HttpResponse::get_date() {
    char buf[1000];
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    return buf;
 }

std::string HttpResponse::build_response() {
     std::string status;
    std::ifstream file{_filepath};
    if (_method == http::method::M_GET) {
        if (!file) {
            status = status::S_404_OK;
            std::string response = "HTTP/1.1 " + status + end_of_line + "Server: " + server_name + end_of_line +
                "Date: " + get_date() + end_of_line + "Connection: " + connection::C_KeepAlive + end_of_file;
        } else {
            std::string content;
            file >> content;
            std::string response = "HTTP/1.1 " + status + end_of_line + "Server: " + server_name + end_of_line +
                "Date: " + get_date() + end_of_line + "Connection: " + connection::C_KeepAlive + end_of_line +
                "Content-Length: " + std::to_string(file.tellg())  + end_of_line + "Content-Type: " + mime_type::determine_content_type(_filepath) + end_of_file + content;
        }
    }
    if (_method == method::M_HEAD) {
        if (!file) {
            status = status::S_404_OK;
            std::string response = "HTTP/1.1 " + status + end_of_line + "Server: " + server_name + end_of_line +
                "Date: " + get_date() + end_of_line + "Connection: " + connection::C_KeepAlive + end_of_file;
        } else {
            std::string content;
            file >> content;
            std::string response = "HTTP/1.1 " + status + end_of_line + "Server: " + server_name + end_of_line +
                "Date: " + get_date() + end_of_line + "Connection: " + connection::C_KeepAlive + end_of_line +
                "Content-Length: " + std::to_string(file.tellg())  + end_of_line + "Content-Type: " + mime_type::determine_content_type(_filepath) + end_of_file ;
        }
    }
 }

};