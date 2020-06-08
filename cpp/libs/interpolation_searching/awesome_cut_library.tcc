#include "awesome_cut_library.h"

/**
 * Function generates pseudo random number
 * @tparam T - variable type
 * @param min_number - beginning of the set
 * @param max_number - end of the set
 * @return pseudo random number
 */
template<typename T>
T random_number_generator(T min_number, T max_number) {
    std::random_device r_dev;
    std::mt19937_64 rng(r_dev()); // strange sigsegv for mt19937
    std::uniform_int_distribution<T> u_int_dist(min_number, max_number);

    return u_int_dist(rng);
}

/**
 * Function sends specified value to the output stream
 * @tparam T - variable type
 * @param out_stream - output stream
 * @param value - value which will be sent on the output
 * @return output stream
 */
template<typename T>
std::ostream &send_on_output(std::ostream &out_stream, T value) {
    out_stream << value;
    return out_stream;
}

/**
 * Function creates file with data to examine
 * @tparam T - variable type for max and min number in output_file_data struct
 * @param cfd - universal reference to output_file_data struct
 * @return true if it succeeds, otherwise false
 */
template<typename T>
bool create_file(output_file_data<T> &&cfd) {
    std::ofstream out_file;
    std::size_t number_of_elements;
    std::size_t number_of_queries;
    std::vector<T> random_numbers_container;
    std::set<T> searching_values;

    out_file.open(cfd.file_name, std::ios::out);

    if (not out_file.is_open()) {
        return false;
    }

    out_file << cfd.number_of_data_sets << std::endl;

    for (std::size_t i = 0; i < cfd.number_of_data_sets; i++) {
        number_of_elements = random_number_generator<std::size_t>(1, 20);
        out_file << number_of_elements << std::endl;

        for (std::size_t j = 0; j < number_of_elements; j++) {
            random_numbers_container.push_back(random_number_generator<int>(cfd.min_number, cfd.max_number));
        }

        std::sort(random_numbers_container.begin(), random_numbers_container.end());

        for (std::size_t j = 0; j < number_of_elements; j++) {
            out_file << random_numbers_container[j] << " ";
        }

        out_file << std::endl;
        number_of_queries = random_number_generator(1, 10);
        out_file << number_of_queries << std::endl;

        while (searching_values.size() != number_of_queries) {
            searching_values.insert(random_number_generator(cfd.min_number, cfd.max_number));
        }

        for (const auto &number : searching_values) {
            out_file << number << " ";
        }

        out_file << std::endl;
    }

    out_file.close();

    return true;
}

/**
 * Function creates output_file_data structure and assigns value to it fields
 * @tparam T variable type for max and min number in output_file_data struct
 * @return output_file_data struct
 */
template<typename T>
output_file_data<T> assign_file_data() {
    output_file_data<T> ofd{};

    std::cout << "File name: ";
    std::cin >> ofd.file_name;
    check_file_name(ofd.file_name);

    std::cout << "Number of data sets: ";
    std::cin >> ofd.number_of_data_sets;

    check_input(std::cin, ofd.number_of_data_sets);

    while (ofd.number_of_data_sets < 0 || ofd.number_of_data_sets > MAX_DATA_SETS) {
        std::cout << "Bad value! Value must be in range from 0 to " << MAX_DATA_SETS << "." << std::endl;
        std::cout << ">> ";
        std::cin >> ofd.number_of_data_sets;
        check_input(std::cin, ofd.number_of_data_sets);
    }

    auto insert_min = [&ofd]() -> void {
        std::cout << "Min number: ";
        std::cin >> ofd.min_number;
        check_input(std::cin, ofd.min_number);
    };

    auto insert_max = [&ofd]() -> void {
        std::cout << "Max number: ";
        std::cin >> ofd.max_number;
        check_input(std::cin, ofd.max_number);
    };

    std::cout << "Min number: ";
    std::cin >> ofd.min_number;

    check_input(std::cin, ofd.min_number);

    while (std::abs(ofd.min_number) > MAX_NUMBER) {
        std::cout << "Bad value! Value must be in range from -2^48 to 2^48." << std::endl;
        insert_min();
    }

    std::cout << "Max number: ";
    std::cin >> ofd.max_number;

    check_input(std::cin, ofd.max_number);

    while (std::abs(ofd.max_number) > MAX_NUMBER) {
        std::cout << "Bad value! Value must be in range from -2^48 to 2^48." << std::endl;
        insert_max();
    }

    while (ofd.min_number > ofd.max_number) {
        std::cout << "Bad range! Minimal value cannot be bigger than maximum value." << std::endl;
        insert_max();
        insert_min();
    }

    return ofd;
}
