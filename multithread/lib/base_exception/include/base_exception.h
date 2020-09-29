//
// Created by kira on 3/23/20.
//

#ifndef PROJECT_INCLUDE_BASE_EXCEPTION_H_
#define PROJECT_INCLUDE_BASE_EXCEPTION_H_

#include <exception>
#include <string>


namespace base_exception {
class Exception : public std::exception {
 public:
    explicit Exception(std::string es);

    [[nodiscard]] const char *what() const noexcept override;

 private:
    std::string _errstr;
};
}  // namespace base_exception


#endif  // PROJECT_INCLUDE_BASE_EXCEPTION_H_
