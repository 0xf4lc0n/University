#ifndef HUFFMAN_ALGORITHM_EXCEPTIONS_H
#define HUFFMAN_ALGORITHM_EXCEPTIONS_H

#include <stdexcept>
namespace MyExceptions {
    class CustomRunTimeError : public std::runtime_error {
        public:
            CustomRunTimeError(const std::string & what_arg);
            CustomRunTimeError(const char * what_arg);
            ~CustomRunTimeError() = default;
    };
}

#endif //HUFFMAN_ALGORITHM_EXCEPTIONS_H
