#include "exceptions.h"

MyExceptions::CustomRunTimeError::CustomRunTimeError(const std::string &what_arg) : runtime_error(what_arg) {}

MyExceptions::CustomRunTimeError::CustomRunTimeError(const char *what_arg) : runtime_error(what_arg) {}

