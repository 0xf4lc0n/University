#include <iostream>
#include <chrono>
#include <fstream>
#include "c_array.h"
#include "stack_size.h"

/**
 * Fuction does the following things:
 * runs algorithm
 * calculates algorithm's execution time
 * saves results to file
 * @tparam T - sorting algorithm function type
 * @tparam S - class type
 * @param sort_algorithm - function object representing sorting algorithm
 * @param arr - CArray object
 * @param os - output stream
 */
template<typename T, typename S>
void log_and_process(T &&sort_algorithm, CArray<S> &arr, std::ostream &os) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_algorithm();
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    os << arr.get_comparisons() << ":" << arr.get_swaps() << ":" << elapsed.count() << std::endl;
}

int main() {
    const int SIZES[3] = {100, 1000, 1000000};
    const std::string POS_TYPE[4] = {"not ordered", "ordered", "reversed", "partial order"};
    std::ofstream out_file;

    out_file.open("logs.txt", std::ios::out);

    if (not out_file) {
        std::cerr << "[Error] Cannot open log file!" << std::endl;
        return EXIT_FAILURE;
    }

    if (is_linux) {
        change_stack_size();
    }

    // Process all sort algorithms
    for (int i = 0; i < 3; i++) {
        std::cout << "Processing for " << SIZES[i] << " elements" << std::endl;

        CArray<int> C1{SIZES[i]};

        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                std::cout << "* Not ordered" << std::endl;
                C1.generate_values();
            } else if (j == 1) {
                std::cout << "* Ordered" << std::endl;
                C1.generate_values();
                C1.heap_sort();
            } else if (j == 2) {
                std::cout << "* Reversed" << std::endl;
                C1.generate_values();
                C1.heap_sort();
                C1.reverse();
            } else {
                std::cout << "* Partial order" << std::endl;
                C1.generate_values();
                C1.heap_sort();
                C1.randomize(10);
            }

            CArray<int> C2{C1};
            CArray<int> C3{C1};
            CArray<int> C4{C1};

            // Exclude cocktail sort for 1000000 unsorted, reversed and partially sorted array
            if (i != 2 or j == 1) {
                std::cout << "Cocktail sort" << std::endl;
                out_file << "cocktail_sort:" << SIZES[i] << ":" << POS_TYPE[j] << ":";
                std::function<void(void)> cocktail = [&C1]() { C1.cocktail_shaker_sort(); };
                log_and_process(cocktail, C1, out_file);
            }

            if (i != 2 or is_linux) {
                std::cout << "Quicksort Lomuto" << std::endl;
                out_file << "quick_l:" << SIZES[i] << ":" << POS_TYPE[j] << ":";
                std::function<void(void)> quick_l = [&C2]() { C2.quick_sort('l'); };
                log_and_process(quick_l, C2, out_file);

                std::cout << "Quicksort Hoare" << std::endl;
                out_file << "quick_h:" << SIZES[i] << ":" << POS_TYPE[j] << ":";
                std::function<void(void)> quick_h = [&C3]() { C3.quick_sort('h'); };
                log_and_process(quick_h, C3, out_file);
            }

            std::cout << "Heapsort" << std::endl;
            out_file << "heap:" << SIZES[i] << ":" << POS_TYPE[j] << ":";
            std::function<void(void)> heap = [&C4]() { C4.heap_sort(); };
            log_and_process(heap, C4, out_file);
        }
        std::cout << "----------------------" << std::endl;
    }
    out_file.close();

    return 0;
}
