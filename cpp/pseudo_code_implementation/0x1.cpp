#include <iostream>
#include <fstream>
#include <memory>
#include "set_manipulation.h"

namespace ins = input_sanitization;

int main() {
    std::size_t number_of_elements = 0;
    int subsets_number = 0;
    int current_index = 0;
    int copy_of_subsets_number = 0;
    std::ofstream out_file;

    std::cout << "Number of elements: ";
    std::cin >> number_of_elements;
    ins::check_input(number_of_elements);

    while (number_of_elements > 26) {
        std::cout << "Error! Current implementation doesn't support sets which contains more than 26 elements." << std::endl;
        std::cout << ">> ";
        std::cin >> number_of_elements;
        ins::check_input(number_of_elements);
    }

    auto number_set = std::make_unique<int[]>(number_of_elements);
    auto char_set = std::make_unique<char[]>(number_of_elements);

    fill_char_set(char_set, number_of_elements);
    out_file.open("0x1.txt", std::ios::out);

    if (not out_file.is_open()) {
        std::cout << "Error! File cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    do {
        // Display current subset
        print_set(number_set, char_set, number_of_elements, out_file);
        // Increment number of created subsets
        subsets_number++;
        current_index = 0;
        copy_of_subsets_number = subsets_number;

        // Calculate index of value to display or to hide
        while (copy_of_subsets_number % 2 == 0) {
            copy_of_subsets_number /= 2;
            current_index++;
        }

        // Displaying/hiding characters (1 - display, 0 - hide)
        if (current_index <= number_of_elements) {
            number_set[current_index] = 1 - number_set[current_index];
        }

    } while (current_index < number_of_elements);

    out_file.close();

    return 0;
}