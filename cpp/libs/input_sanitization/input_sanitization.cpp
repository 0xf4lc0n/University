#include "input_sanitization.h"

namespace input_sanitization {
    void clear_stream(std::istream &is) {
        is.clear();
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string generate_error_message(const ERROR_TYPE &err, const error_details &err_det) {
        std::stringstream error_stream;

        if (err == ERROR_TYPE::TYPE_ERROR) {
            return {"Bad value type!"};
        } else if (err == ERROR_TYPE::RANGE_ERROR) {
            error_stream << "Value is to big or to small. Proper range for value [" << err_det.min_value << " " <<
                         err_det.max_value << "]!";
            return error_stream.str();
        } else if (err == ERROR_TYPE::FILE_TYPE_ERROR) {
            error_stream << "Bad value type in line number " << err_det.input_file_line_number
                         << "! Check file and insert proper value.";
            return error_stream.str();
        } else if (err == ERROR_TYPE::FILE_RANGE_ERROR){
            error_stream << "Bad value range in line number " << err_det.input_file_line_number
                         << "! Proper range for value [" << err_det.min_value << " " << err_det.max_value
                         << "] Check file and insert proper value.";
            return error_stream.str();
        } else {
            return {"Unexpected error occurred!"};
        }
    }

    bool is_file_extension_valid(std::string &f_name) {
        auto dot_index = f_name.find_last_of('.');

        if (dot_index == std::string::npos) {
            f_name.append(".txt");
            return true;
        } else {
            return !(f_name.substr(dot_index + 1) != "txt");
        }
    }
}

