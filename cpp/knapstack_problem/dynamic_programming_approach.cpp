#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "../libs/input_sanitization/input_sanitization.tcc"
#include "../libs/backpack/backpack_problem.tcc"
#include "../libs/backpack/subject.tcc"

namespace isa = input_sanitization;

int main() {
    std::vector<Subject<int>> subjects;
    std::string file_name;

    std::cout << "File name: ";
    std::cin >> file_name;
    isa::is_file_extension_valid(file_name);

    std::ifstream in_file(file_name);

    if (not in_file.is_open()) {
        std::cerr << "[Error] File can't be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    int backpack_capacity = 0;
    std::string subject_name;
    int subject_price = 0;
    int subject_weight = 0;

    in_file >> backpack_capacity;
    isa::check_input(backpack_capacity, in_file);

    while (not in_file.eof()) {
        in_file >> subject_name;
        //isa::check_input(subject_name, in_file);

        in_file >> subject_weight;
        isa::check_input(subject_weight, in_file);

        in_file >> subject_price;
        isa::check_input(subject_price, in_file);

        subjects.emplace_back(Subject<int>(subject_name, subject_weight, subject_price));
    }

    in_file.close();

    auto price_pack = std::make_unique<std::unique_ptr<int[]>[]>(subjects.size());
    auto subject_pack = std::make_unique<std::unique_ptr<int[]>[]>(subjects.size());

    for (std::size_t i = 0; i < subjects.size(); i++) {
        price_pack[i] = std::make_unique<int[]>(backpack_capacity);
        subject_pack[i] = std::make_unique<int[]>(backpack_capacity);
    }

    auto first_s_weight = subjects[0].get_weight();
    auto first_s_price = subjects[0].get_price();

    for (std::size_t i = 0; i < backpack_capacity; i++) {
        if (first_s_weight <= i + 1) {
            price_pack[0][i] = first_s_price;
            subject_pack[0][i] = 1;
        } else {
            price_pack[0][i] = 0;
            subject_pack[0][i] = 0;
        }
    }

    for (std::size_t i = 1; i < subjects.size(); i++) {
        for (std::size_t j = 0; j < backpack_capacity; j++) {
            if (subjects[i].get_weight() > j + 1) {
                price_pack[i][j] = price_pack[i - 1][j];
                subject_pack[i][j] = subject_pack[i - 1][j];
            } else {
                auto s_price = price_pack[i - 1][j - subjects[i].get_weight()] + subjects[i].get_price();
                if (price_pack[i - 1][j] > s_price) {
                    price_pack[i][j] = price_pack[i - 1][j];
                    subject_pack[i][j] = subject_pack[i - 1][j];
                } else {
                    price_pack[i][j] = s_price;
                    subject_pack[i][j] = i + 1;
                }
            }
        }
    }

    // Print P table
    display::result_matrix(price_pack, backpack_capacity, subjects.size());

    std::cout << "--------------------" << std::endl;

    // Print Q table
    display::result_matrix(subject_pack, backpack_capacity, subjects.size());

    return 0;
}