//
// Created by kira on 3/23/20.
//

#include "file_descriptor.h"
#include "base_exception.h"

#include <unistd.h>

using base_exception::Exception;

namespace file_descriptor {
FileDescriptor::FileDescriptor(int fd) : _fd(fd) {}

FileDescriptor::FileDescriptor(FileDescriptor &&other) noexcept {
    if (this == &other) {
        return;
    }
    this->_fd = other._fd;
    other._fd = -1;
}

FileDescriptor::~FileDescriptor() {
    if (_fd != -1) {
        ::close(_fd);
    }
}

void FileDescriptor::close() {
    if (_fd != -1) {
        if (::close(_fd) == -1) {
            throw Exception("inappropriate close");
        }
    }
    _fd = -1;
}

FileDescriptor &FileDescriptor::operator=(FileDescriptor &&other) noexcept {
    this->close();
    if (this->_fd == other._fd) {
        return *this;
    }
    this->_fd = other._fd;
    other._fd = -1;
    return *this;
}

void FileDescriptor::link(FileDescriptor const &other) {
    if (dup2(this->_fd, other._fd) == -1) {
        throw Exception("dup2 failed");
    }
}

int FileDescriptor::fd() const {
    return _fd;
}
FileDescriptor::operator int() const {
    return _fd;
}

Pipe::Pipe() {
    int tmp_pipe[2];
    if (pipe(tmp_pipe) != 0) {
        throw Exception("pipe was not created");
    }
    _read = FileDescriptor(tmp_pipe[READ]);
    _write = FileDescriptor(tmp_pipe[WRITE]);
}

const FileDescriptor &Pipe::read() const {
    return _read;
}

const FileDescriptor &Pipe::write() const {
    return _write;
}

FileDescriptor &&Pipe::read() {
    return std::move(_read);
}

FileDescriptor &&Pipe::write() {
    return std::move(_write);
}
}  // namespace file_descriptor
