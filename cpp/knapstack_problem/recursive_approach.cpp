#include <iostream>
#include <fstream>
#include "../libs/backpack/backpack_problem.tcc"
#include "../libs/input_sanitization/input_sanitization.tcc"

namespace isa = input_sanitization;

int main() {
    std::string file_name;

    std::cout << "File name: ";
    std::cin >> file_name;
    isa::is_file_extension_valid(file_name);

    std::ifstream in_file(file_name);

    if (not in_file.is_open()) {
        std::cerr << "[Error] File can't be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    int data_sets = 0;
    int backpack_capacity = 0;
    int number_of_elements = 0;
    int weight = 0;
    std::vector<int> weights;

    in_file >> data_sets;
    isa::check_input(data_sets, in_file, 0x0, 0xF4240);

    while (not in_file.eof()) {
        in_file >> backpack_capacity;
        isa::check_input(backpack_capacity, in_file, 0x0, 0xF4240);
        in_file >> number_of_elements;
        isa::check_input(number_of_elements, in_file, 0x0, 0xF4240);

        for (int i = 0; i < number_of_elements; i++) {
            in_file >> weight;
            isa::check_input(weight, in_file, 0x0, 0xF4240);
            weights.push_back(weight);
        }

        auto result_sequence = recursive::pack_backpack(weights, backpack_capacity);

        if (not result_sequence.empty()) {
            std::cout << backpack_capacity << " = ";
            for (const auto & e : result_sequence) {
                std::cout << e << " ";
            }
        } else {
            std::cout << "BRAK!";
        }

        std::cout << std::endl;

        weights.clear();
    }

    in_file.close();

    return 0;
}