#include "awesome_cut_library.h"

std::ofstream create_result_file(const std::string &file_name) {
    std::ofstream output_file;
    output_file.open(file_name, std::ios::out);

    if (not output_file.is_open()) {
        throw;
    } else {
        return std::move(output_file);
    }
}

int interpolation_search(std::vector<int> &vec, int searching_value) {
    std::size_t start = 0;
    std::size_t end = vec.size() - 1;
    std::size_t current_index;

    while (start <= end and searching_value >= vec[start] and searching_value <= vec[end]) {
        current_index = start + ((double((end - start)) / (vec[end] - vec[start])) * (searching_value - vec[start]));

        if (vec[current_index] == searching_value) {
            if (current_index > 0) {
                while (vec[current_index - 1] == searching_value)
                    current_index--;
            }
            return current_index;
        } else if (searching_value > vec[current_index]) {
            start = current_index + 1;
        } else {
            end = current_index - 1;
        }
    }

    return -1;
}

int calculate_equal_numbers(std::vector<int> &vec, int index, int number) {
    if (index < 0) {
        return 0;
    }

    int amount = 0;

    while (vec[index++] == number) {
        amount++;
    }

    return amount;
}

bool load_data_from_file(const std::string &file_name) {
    std::ifstream input_file;
    input_file.open(file_name, std::ios::in);

    if (not input_file.is_open()) {
        std::cerr << "File cannot be opened!" << std::endl;
        return false;
    }

    std::size_t data_sets;
    std::size_t elements;
    std::size_t query_number;
    int number;
    int index;
    std::vector<int> numbers_array;
    std::set<int> number_set;
    std::string result_file_name = file_name.substr(0, file_name.find_last_of('.')) + "_out.txt";

    std::ofstream result_file;

    input_file >> data_sets;

    for (std::size_t i = 0; i < data_sets; i++) {
        input_file >> elements;

        for (std::size_t j = 0; j < elements; j++) {
            input_file >> number;
            numbers_array.push_back(number);
            number_set.insert(number);
        }

        input_file >> query_number;

        result_file = create_result_file(result_file_name);

        for (std::size_t j = 0; j < query_number; j++) {
            input_file >> number;
            index = interpolation_search(numbers_array, number);
            result_file << "(" << calculate_equal_numbers(numbers_array, index, number) << " " << index << ") ";
        }

        result_file << std::endl;

        for (auto const &element : number_set) {
            result_file << element << " ";
        }

        result_file.close();
    }
    input_file.close();

    return true;
}
