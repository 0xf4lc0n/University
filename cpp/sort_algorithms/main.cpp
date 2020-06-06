#include <iostream>
#include <chrono>
#include <fstream>
#include "c_array.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    static constexpr bool is_linux = false;
#else
    static constexpr bool is_linux = true;
    #include <sys/resource.h>
#endif

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
    if (is_linux) {
        // Set stack size
        // 8 MB
        const rlim_t stack_size = 8 * 1024 * 1024;
        struct rlimit rl;
        // Download current configuration
        int err_code = getrlimit(RLIMIT_STACK, &rl);

        if (err_code == 0) {
            // Set new stack size
            rl.rlim_cur = stack_size;
            err_code = setrlimit(RLIMIT_STACK, &rl);
            if (err_code != 0) {
                std::cerr << "Error code: " << err_code << std::endl;
                return EXIT_FAILURE;
            }

        } else {
            std::cerr << "Set size cannot be modified!" << std::endl;
            std::cerr << "Due to this issue quciksort called for ordered set of data will cause stack overflow!"
                      << std::endl;
            std::cerr << "Aborting..." << std::endl;
            return EXIT_FAILURE;
        }
    }
    const int SIZES[3] = {100, 1000, 1000000};
    const std::string POS_TYPE[4] = {"not ordered", "ordered", "reversed", "partial order"};
    std::ofstream out_file;

    out_file.open("logs2.txt", std::ios::out);

    if (not out_file) {
        std::cerr << "[Error] Cannot open log file!" << std::endl;
        return EXIT_FAILURE;
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
