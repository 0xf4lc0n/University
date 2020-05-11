#ifndef LAB8_INPUT_SANITIZATION_H
#define LAB8_INPUT_SANITIZATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <limits>

namespace input_sanitization {
    /**
     * Error types
     */
    enum class ERROR_TYPE{TYPE_ERROR, RANGE_ERROR, FILE_TYPE_ERROR, FILE_RANGE_ERROR};

    /**
     * Structure contains information about error
     */
    struct error_details {
        int input_file_line_number;
        long min_value;
        long max_value;
    };

    /**
     * Clear input stream by rejecting characters that cause error
     * @param is - input stream
     */
    void clear_stream(std::istream &is);

    /**
     * Function creates error message
     * @param err - error type
     * @return string representing error
     */
    std::string generate_error_message(const ERROR_TYPE & err, const error_details & err_det);

    /**
     * Function checks if file name has proper extension
     * @param f_name - reference to variable which store file name
     */
    bool is_file_extension_valid(std::string &f_name);

}

#endif //LAB8_INPUT_SANITIZATION_H
