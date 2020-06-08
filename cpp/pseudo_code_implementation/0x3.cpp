#include <iostream>
#include <fstream>
#include <memory>
#include "set_manipulation.h"

namespace ins = input_sanitization;

int main() {
    int number = 0;
    std::ofstream out_file;

    std::cout << "Number: ";
    std::cin >> number;
    ins::check_input(number);

    std::vector<int> distributed_numbers_array(10, 0);
    std::vector<int> amount_of_dn_array(10, 0);
    int start_index = 0;

    distributed_numbers_array[0] = number;
    amount_of_dn_array[0] = 1;

    out_file.open("0x3.txt", std::ios::out);

    if (not out_file.is_open()) {
        std::cout << "Error! File cannot be opened!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Prints empty line
    print_factor_array(distributed_numbers_array, amount_of_dn_array, number, out_file);

    while (distributed_numbers_array[0] > 1) {
        int sum = 0;

        if (distributed_numbers_array[start_index] == 1) {
            sum += amount_of_dn_array[start_index];
            start_index -= 1;
        }

        sum += distributed_numbers_array[start_index];
        amount_of_dn_array[start_index] -= 1;
        int factor = distributed_numbers_array[start_index] - 1;

        if (amount_of_dn_array[start_index] > 0) {
            start_index += 1;
        }

        distributed_numbers_array[start_index] = factor;
        amount_of_dn_array[start_index] = sum / factor;
        factor = sum % factor;

        if (factor != 0) {
            start_index += 1;
            distributed_numbers_array[start_index] = factor;
            amount_of_dn_array[start_index] = 1;
        }

        print_factor_array(distributed_numbers_array, amount_of_dn_array, number, out_file);
    }
    out_file.close();
}