//
// Created by kira on 3/31/20.
//

#ifndef PROJECT_LIB_TCP_CONNECTION_H_
#define PROJECT_LIB_TCP_CONNECTION_H_

#include "file_descriptor.h"
#include "socket_properties.h"

#include <string>
#include <chrono>

using std::chrono_literals::operator""s;
using std::chrono_literals::operator""us;

namespace tcp {
class Connection {
 public:
    Connection() = default;

    explicit Connection(file_descriptor::FileDescriptor fd);
    Connection(file_descriptor::FileDescriptor fd, Properties properties);
    Connection(std::string ip, uint16_t port);

    Connection(Connection &&other) noexcept = default;
    Connection &operator=(Connection &&other) noexcept = default;

    size_t write(const void *data, size_t size);
    void write_exact(const void *data, size_t size);
    Connection &operator <<(const std::string &data);

    size_t read(void *data, size_t size);
    void read_exact(void *data, size_t size);
    Connection &operator >>(std::string &data);

    [[nodiscard]] bool is_opened() const;
    [[nodiscard]] bool is_blocking() const;
    [[nodiscard]] const Properties &props() const;
    [[nodiscard]] const file_descriptor::FileDescriptor &fd() const;
 private:
    void set_timeout(std::chrono::seconds seconds = 0s, std::chrono::microseconds microseconds = 0us);

    file_descriptor::FileDescriptor _fd;
    Properties _properties;
};
}  // namespace tcp

#endif //PROJECT_LIB_TCP_CONNECTION_H_
