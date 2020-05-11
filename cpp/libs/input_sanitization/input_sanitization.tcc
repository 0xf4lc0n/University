#ifndef LAB8_INPUT_SANITIZATION_TCC
#define LAB8_INPUT_SANITIZATION_TCC

#include "input_sanitization.h"
#include <memory>

namespace input_sanitization {
    namespace internal_implementations {
        /**
         * Function allow to retype values which are rejected
         * This function is designated to use by implementation. It's internal function which should not be used independently.
         * @param is - input stream
         * @param var_store_input - variable which will store provided values
         */

        template<typename T>
        void _retype_values(T &var_storing_input, const std::string &error_msg) noexcept {
            std::cerr << "[Error] " << error_msg << std::endl;
            std::cerr << ">> ";
            std::cin >> var_storing_input;
        }

        /**
         *  Function checks input for numeric variables
         * @tparam T - type of value which store inputed value
         * @tparam S - type of values which define range
         * @param var_store_input - reference to variable which store input
         * @param is - input stream
         * @param min - minimal acceptable value
         * @param max - maximal acceptable value
         * @param line_number - actual line in input file (requires user's mechanism to determine/count
         * actual number of line in file)
         */
        template<typename T, typename S = long>
        void _check_input(T &var_store_input, std::istream &is = std::cin, S min = 0x0, S max = 0xFFFFFFFFL,
                          int line_number = -1) {
            if (is.fail() or var_store_input < min or var_store_input > max) {
                error_details err_det{line_number, min, max};
                std::string error_msg;
                std::cin.setstate(std::ios_base::failbit);

                while (std::cin.fail()) {
                    if (line_number != -1) {
                        error_msg = generate_error_message(ERROR_TYPE::FILE_TYPE_ERROR, err_det);

                        if (var_store_input < min or var_store_input > max) {
                            error_msg = generate_error_message(ERROR_TYPE::FILE_RANGE_ERROR, err_det);
                        }
                    } else {
                        error_msg = generate_error_message(ERROR_TYPE::TYPE_ERROR, err_det);

                        if (var_store_input < min or var_store_input > max) {
                            error_msg = generate_error_message(ERROR_TYPE::RANGE_ERROR, err_det);
                        }
                    }
                    clear_stream(std::cin);
                    internal_implementations::_retype_values(var_store_input, error_msg);
                }
            }
        }
    }

    /**
     * Wrapper function checking input for fundamental types
     * @tparam T - type of value which store inputed value
     * @tparam S - type of values which define range
     * @param var_store_input - reference to variable which store input
     * @param is - input stream
     * @param min - minimal acceptable value
     * @param max - maximal acceptable value
     * @param line_number - actual line in input file (requires user's mechanism to determine/count
     * actual number of line in file)
     */
    template<typename T, typename S = long>
    void check_input(T &var_store_input, std::istream &is = std::cin, S min = 0x0, S max = 0xFFFFFFFFL,
                     int line_number = -1) {

        if constexpr (not std::is_same_v<T, std::string> and std::is_fundamental_v<T>) {
            if constexpr (std::is_same_v<T, char>) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                internal_implementations::_check_input(var_store_input, is, min, max, line_number);
            }
        }
    }
}
#endif //LAB8_INPUT_SANITIZATION_TCC