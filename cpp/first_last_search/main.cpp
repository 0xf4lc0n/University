#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "searching.h"
#include "input_sanitization.tcc"

namespace se = searching_element;
namespace wrap = searching_element::wrappers;
namespace isn = input_sanitization;

int main() {
    int number_of_data_sets = 0;
    int searched_value = 0;
    std::vector<std::string> results;
    se::array_details arr_det;
    se::smart_2D &md_arr = arr_det.dimensional_array;
    std::stringstream result_stream;
    std::ifstream in_file;
    constexpr int MAX = 0x8000;
    constexpr int MIN = -0x8000;

    in_file.open("in_custom.txt", std::ios::in);
    if (not in_file.is_open()) {
        std::cout << "File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    in_file >> number_of_data_sets;
    isn::check_input(number_of_data_sets, in_file);

    while (number_of_data_sets) {
        in_file >> arr_det.rows;
        isn::check_input(arr_det.rows, in_file, 1, 100);
        in_file >> arr_det.columns;
        isn::check_input(arr_det.columns, in_file, 1, 100);
        md_arr = std::make_unique<se::smart_1D[]>(arr_det.rows);

        for (std::size_t i = 0; i < arr_det.rows; i++) {
            md_arr[i] = std::make_unique<int[]>(arr_det.columns);
        }

        for (std::size_t i = 0; i < arr_det.rows; i++) {
            for (std::size_t j = 0; j < arr_det.columns; j++) {
                in_file >> md_arr[i][j];
                isn::check_input(md_arr[i][j], in_file, MIN, MAX);
            }
        }

        in_file >> searched_value;
        isn::check_input(searched_value, in_file);

        auto first_occ = wrap::iterative_first_occurring(arr_det, searched_value);

        /*
         * If first search return structure like {-1, -1} for searched value it's mean that there is no such value
         * in array so calling next searching is pointless.
        */
        if (first_occ.row != -1) {
            auto last_occ = wrap::iterative_last_occurring(arr_det, searched_value);
            auto r_first_occ = wrap::recursive_first_occurring(arr_det, searched_value);
            auto r_last_occ = wrap::recursive_last_occurring(arr_det, searched_value);

            result_stream << std::setw(10) << std::left << "RekPier: " << searched_value << " w " << "("
                          << r_first_occ.row << "," << r_first_occ.column
                          << ")";
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "RekOst: " << searched_value << " w " << "("
                          << r_last_occ.row << "," << r_last_occ.column
                          << ")";
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "IterPier: " << searched_value << " w " << "("
                          << first_occ.row << "," << first_occ.column
                          << ")";
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "IterOst: " << searched_value << " w " << "("
                          << last_occ.row << "," << last_occ.column
                          << ")";
            results.push_back(result_stream.str());
            result_stream.str(std::string());

        } else {
            result_stream << std::setw(10) << std::left << "RekPier: " << "nie ma " << searched_value;
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "RekOst: " << "nie ma " << searched_value;
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "IterPier: " << "nie ma " << searched_value;
            results.push_back(result_stream.str());
            result_stream.str(std::string());
            result_stream << std::setw(10) << std::left << "IterOst: " << "nie ma " << searched_value;
            results.push_back(result_stream.str());
            result_stream.str(std::string());
        }
        results.emplace_back("--------------");
        number_of_data_sets--;
    }

    for (const auto &result : results) {
        std::cout << result << std::endl;
    }

    return 0;
}