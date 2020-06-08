#include <iostream>
#include <fstream>
#include <memory>
#include "set_manipulation.h"


int main() {
    int set_size = 0;
    int subset_size = 0;
    std::ofstream out_file;


    input_number_of_elements("set", set_size);
    input_number_of_elements("subset", subset_size);

    while (subset_size >= set_size) {
        std::cout << "Set size must be larger than subset size!" << std::endl;
        input_number_of_elements("set", set_size);
        input_number_of_elements("subset", subset_size);
    }

    auto n_subset = std::make_unique<int[]>(subset_size);
    auto c_set = std::make_unique<char[]>(set_size);

    fill_char_set(c_set, set_size);
    out_file.open("0x2.txt", std::ios::out);

    if (not out_file.is_open()) {
        std::cout << "Error! File cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (std::size_t i = 0; i < subset_size; i++) {
        n_subset[i] = i;
    }

    int end_index = subset_size - 1;

    while (end_index >= 0) {
        print_set_lg(n_subset, c_set, subset_size, out_file);

        if (n_subset[subset_size - 1] == set_size - 1) {
            end_index -= 1;
        } else {
            end_index = subset_size - 1;
        }

        if (end_index >= 0) {
            for (int i = subset_size - 1; i >= end_index; i--) {
                // Take next character from set
                n_subset[i] = n_subset[end_index] + i - end_index + 1;
            }
        }
    }

    out_file.close();

    return 0;
}