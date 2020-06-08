#include <iostream>
#include <fstream>
#include <vector>
#include "recursion_and_merge.h"
#include "input_sanitization.tcc"

namespace isn = input_sanitization;
using namespace merge;

int main() {
    std::ifstream in_file;

    in_file.open("in.txt", std::ios::in);

    if (not in_file.is_open()) {
        std::cerr << "Error! File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    int data_sets = 0;
    int number = 0;
    std::vector<int> numbers;
    std::vector<int> auxiliary_vector;
    constexpr long max = 0x100000000000;
    constexpr long min = -max;
    int elements = 0;

    in_file >> data_sets;
    isn::check_input(data_sets, in_file);

    if (data_sets < 1 or data_sets > 215) {
        std::cerr << "To many data sets! Data sets must be in range <1, 215>" << std::endl;
        return EXIT_FAILURE;
    }

    while (data_sets) {
        in_file >> elements;
        isn::check_input(elements, in_file);

        while (elements) {
            in_file >> number;
            isn::check_input(number, in_file, min, max);
            numbers.push_back(number);
            elements--;
        }
        data_sets--;

        auxiliary_vector.resize(numbers.size());

        std::cout << merge_sort(numbers, auxiliary_vector, 0, auxiliary_vector.size() - 1) << std::endl;

        numbers.clear();
        auxiliary_vector.clear();
    }

    in_file.close();
}

