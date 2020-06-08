#include <iostream>
#include <exception>
#include <limits>
#include <new>
#include <istream>

struct sub_array_bounds {
    std::size_t row_begin, col_begin;
    std::size_t row_end, col_end;
    int max_sum;
};

struct row_max_bounds {
    std::size_t start;
    std::size_t end;
    int max;
};

template<typename T>
void check_input(std::istream &is, T &var_store_input);

template<typename T>
T **create_2d_array(std::size_t rows, std::size_t cols);

template<typename T>
T MOD(T number) {
    return (number > 0) ? number : -number;
}

template<typename T>
row_max_bounds kadane_algorithm(const T *row_sum_array, std::size_t len);

template<typename T>
sub_array_bounds find_max_sub_array(T **dimensional_array, std::size_t rows, std::size_t cols);

int main() {
    std::size_t rows = 0;
    std::size_t cols = 0;
    std::size_t data_packet_amount = 0;
    constexpr std::size_t max_val = std::numeric_limits<short>::max();
    int **my_2d_array;

    // Insert how many arrays will be created and examined
    std::cin >> data_packet_amount;
    check_input(std::cin, data_packet_amount);

    // For loop processing algorithm for inserted amount of arrays
    for (std::size_t loop_counter = 0; loop_counter < data_packet_amount; loop_counter++) {

        // Insert number of columns and rows (from 0 to 100 range)
        // If negative number will be assigned to std::size_t, it will contain result express by that formula
        // If negative number will be provided, std:size_t will contain
        // negative number + std::numeric_limits<unsigned long >::max() + 1
        do {
            std::cout << "Rows >> ";
            std::cin >> rows;
            check_input(std::cin, rows);
            std::cout << "Cols >> ";
            std::cin >> cols;
            check_input(std::cin, cols);
        } while (rows > 100 or cols > 100);

        // Allocate dynamic array
        try {
            my_2d_array = create_2d_array<int>(rows, cols);
        } catch (const std::bad_alloc &e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }

        // Assign values to array
        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < cols; j++) {
                std::cin >> my_2d_array[i][j];
                check_input(std::cin, my_2d_array[i][j]);
                if (MOD(my_2d_array[i][j]) > max_val) {
                    my_2d_array[i][j] = 0;
                }
            }
        }

        // Find maximum subarray and store information about that structure (start, end indexes and max sum)
        sub_array_bounds max_subarray = find_max_sub_array(my_2d_array, rows, cols);

        // Print maximum sum for subarray
        std::cout << max_subarray.max_sum << std::endl;

        // Deallocate memory on cheap
        for (std::size_t i = 0; i < rows; i++) {
            delete[] my_2d_array[i];
        }

        delete[] my_2d_array;
    }

    return 0;
}

template<typename T>
void check_input(std::istream &is, T &var_store_input) {
    // Until fail bit is set
    while (is.fail()) {
        // Clear error state flags
        is.clear();
        // Reject all characters up to new line character which also is rejected (clearing input stream/buffer)
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Print some stuff
        std::cout << "Input error, bad value type!" << std::endl;
        std::cout << ">> ";
        // And yeah that's obvious
        is >> var_store_input;
    }
}

template<typename T>
T **create_2d_array(std::size_t rows, std::size_t cols) {
    T **array = new T *[rows];

    for (std::size_t i = 0; i < rows; i++) {
        array[i] = new T[cols];
    }

    return array;
}

template<typename T>
row_max_bounds kadane_algorithm(const T *row_sum_array, std::size_t len) {
    T best_sum = 0;
    T current_sum = 0;
    std::size_t current_start = 0;
    std::size_t best_start = 0, best_end = 0;

    // For each column in currently processed row
    for (std::size_t i = 0; i < len; i++) {
        // Add column's value to current row's sum
        current_sum += row_sum_array[i];

        // If sum is negative, move start index and reset sum variable
        if (current_sum < 0) {
            current_start = i + 1;
            current_sum = 0;
        }

        // If current sum is bigger than previous one, update indexes and sum variable
        if (current_sum > best_sum) {
            best_sum = current_sum;
            best_start = current_start;
            best_end = i;
        }
    }

    return {best_start, best_end, best_sum};
}

template<typename T>
sub_array_bounds find_max_sub_array(T **dimensional_array, std::size_t rows, std::size_t cols) {
    // Structure stores max 1D subarray data (start, end indexes and max sum)
    row_max_bounds rmb{};

    // Structure stores max 2D subarray data
    // row's start, end indexes
    // column's start, end indexes
    // sum of all contiguous elements
    sub_array_bounds max_subarray{};

    // Array contains sum of elements in row (in specified range)
    int *row_sum = new int[rows];

    // Main for loop which incrementing col_start index as long as it's lower than total number of columns

    // Loop processing data via columns
    for (std::size_t col_start = 0; col_start < cols; col_start++) {
        // Clear max_sum for each row
        for (std::size_t i = 0; i < rows; i++) {
            row_sum[i] = 0;
        }

        // Sum all contiguous elements in 2D subarray
        // For current column
        for (std::size_t col_end = col_start; col_end < cols; col_end++) {
            // Sum all values from rows
            for (std::size_t row = 0; row < rows; row++) {
                row_sum[row] += dimensional_array[row][col_end];
            }

            // Kadane algorithm searches for maximal sum of contiguous elements
            rmb = kadane_algorithm(row_sum, rows);

            // If maximal subarray is bigger than previous one, update structure
            if (rmb.max > max_subarray.max_sum) {
                max_subarray.max_sum = rmb.max;
                max_subarray.row_begin = rmb.start;
                max_subarray.row_end = rmb.end;
                max_subarray.col_begin = col_start;
                max_subarray.col_end = col_end;
            }
        }
    }

    // Deallocate memory on cheap
    delete[] row_sum;

    return max_subarray;
}
