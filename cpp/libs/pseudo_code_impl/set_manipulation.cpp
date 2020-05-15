#include "set_manipulation.h"

void print_set(const std::unique_ptr<int[]> &n_set, const std::unique_ptr<char[]> &c_set, std::size_t size,
               std::ostream &os) {
    for (int i = 0; i < size; i++) {
        if (n_set[i] == 1) {
            os << c_set[i] << " ";
        }
    }
    os << std::endl;
}

void fill_char_set(std::unique_ptr<char[]> &c_set, std::size_t size) {
    for (int i = 0; i < size; i++) {
        c_set[i] = char(i + 65);
    }
}

void print_set_lg(const std::unique_ptr<int[]> &n_set, const std::unique_ptr<char[]> &c_set, std::size_t subset_size,
                  std::ostream &os) {
    for (std::size_t i = 0; i < subset_size; i++) {
        os << c_set[n_set[i]] << " ";
    }
    os << std::endl;
}

void print_factor_array(std::vector<int> &distributed_numbers, std::vector<int> &amount_of_numbers, int primary_number,
                        std::ostream &os) {
    int sum = 0;
    int current_index = 0;
    while (sum != primary_number) {
        for (int x = 1; x <= amount_of_numbers[current_index]; x++) {
            os << distributed_numbers[current_index] << " ";
            sum += distributed_numbers[current_index];
        }
        current_index++;
    }
    os << std::endl;
}
