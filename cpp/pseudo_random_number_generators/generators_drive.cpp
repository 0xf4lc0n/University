#include <iostream>
#include <fstream>

#include "generators.tcc"
#include "input_sanitization.tcc"

namespace ins = input_sanitization;

void menu();

int main() {
    char choice = '\0';
    LCG<long> lcg_generator;
    long max_value = 0;
    std::size_t numbers_to_generate = 0;
    long seed = 0;

    ACG<long> acg_generator;
    long module = 0;
    int j = 0, k = 0;

    std::string file_name;

    std::cout << "Output file name: ";
    std::cin >> file_name;

    while (not ins::is_file_extension_valid(file_name)) {
        std::cout << "Program supports only txt files!" << std::endl;
        std::cout << ">> ";
        std::cin >> file_name;
    }

    std::ofstream out_file(file_name);

    if (not out_file.is_open()) {
        std::cerr << "[Error] File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    while (choice != 'q') {
        menu();
        std::cin.get();
        std::cin.get(choice);
        ins::check_input(choice);

        switch (choice) {
            case '1':
                std::cout << "Max value: ";
                std::cin >> max_value;
                ins::check_input(max_value);
                std::cout << "Amount of numbers to display: ";
                std::cin >> numbers_to_generate;
                ins::check_input(numbers_to_generate);
                std::cout << "Generator's seed: ";
                std::cin >> seed;
                ins::check_input(seed);

                lcg_generator.reset(max_value, seed);
                lcg_generator.generate_numbers(numbers_to_generate);

                out_file << "LCG" << std::endl;
                out_file << "LCG's factors: ";
                lcg_generator.show_factors(out_file);
                out_file << "Generated numbers: " << std::endl;
                out_file << lcg_generator << std::endl;

                break;
            case '2':
                std::cout << "Amount of numbers to generate: ";
                std::cin >> numbers_to_generate;
                ins::check_input(numbers_to_generate);
                std::cout << "Module: ";
                std::cin >> module;
                ins::check_input(module);
                std::cout << "Pair of numbers [j, k] (split them with space, without coma and brackets): ";
                std::cin >> j >> k;
                ins::check_input(j);
                ins::check_input(k);

                acg_generator.reset(numbers_to_generate, module, j, k);
                acg_generator.generate_numbers();

                out_file << "ACG" << std::endl;
                out_file << "Generated numbers: " << std::endl;
                out_file << acg_generator << std::endl;
                break;
            default:
                if (choice != 'q') {
                    std::cerr << "[Warning] Such option doesn't exist!" << std::endl;
                }
                break;
        }
    }

    out_file.close();

    return 0;
}

void menu() {
    std::cout << "1. LCG" << std::endl;
    std::cout << "2. ACG" << std::endl;
    std::cout << ">> ";
}