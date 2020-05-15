#include <iostream>
#include "../libs/interpolation_searching/awesome_cut_library.h"
#include "../libs/input_sanitization/input_sanitization.tcc"

namespace ins = input_sanitization;

int main() {
    std::string file_name;

    std::cout << "File name: " << std::endl;
    std::cin >> file_name;

    ins::is_file_extension_valid(file_name);
    load_data_from_file(file_name);

    return 0;
}
