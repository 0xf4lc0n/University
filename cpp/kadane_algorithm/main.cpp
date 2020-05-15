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

    // For loop that allow to process algorithm for inserted amount of arrays
    for (std::size_t loop_counter = 0; loop_counter < data_packet_amount; loop_counter++) {

        // Insert columns and rows number
        // If negative number will be assigned to std::size_t, it will contain result express by that formula
        // negative number + std::numeric_limits<unsigned long >::max() + 1
        // and the result will always be between 0 and 100
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

        // Find maximum sum for subarray and return it to variable which store that sum and start/end indexes
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

    // For each element in processing row
    for (std::size_t i = 0; i < len; i++) {
        // Add it to value which store currently processed sum
        current_sum += row_sum_array[i];

        // If sum of processed elements is negative
        // Increment row start index and clear current_sum variable
        if (current_sum < 0) {
            current_start = i + 1;
            current_sum = 0;
        }

        // If sum of processed elements is bigger than previous maximum sum, update index and sum variables
        if (current_sum > best_sum) {
            best_sum = current_sum;
            best_start = current_start;
            best_end = i;
        }
    }

    // Structure storing start and end indexes and the maximum sum of continuous elements
    row_max_bounds rb{best_start, best_end, best_sum};

    return rb;
}

template<typename T>
sub_array_bounds find_max_sub_array(T **dimensional_array, std::size_t rows, std::size_t cols) {
    // Structure that store
    // start_index, end_index and the biggest sum of elements
    // for currently processed row
    row_max_bounds rmb{};

    // Structure that store
    // column_start and column_end indexes
    // row_start and row_end indexes
    // maximal sum of contiguous elements
    // for subarray with the biggest fum of contiguous elements
    sub_array_bounds max_subarray{};

    int *row_sum = new int[rows];

    // Main for loop which incrementing col_start index as long as it's lower than total number of columns
    for (std::size_t col_start = 0; col_start < cols; col_start++) {
        // For each new column start index row_sum array is cleared
        for (std::size_t i = 0; i < rows; i++) {
            row_sum[i] = 0;
        }

        // For each row, add items from col_start to col_end and increase the col_end index if it is lower than
        // total number of columns
        for (std::size_t col_end = col_start; col_end < cols; col_end++) {
            for (std::size_t row = 0; row < rows; row++) {
                row_sum[row] += dimensional_array[row][col_end];
            }

            // Use Kadane algorithm for array row_sum to find maximal sum of contiguous elements
            rmb = kadane_algorithm(row_sum, rows);

            // Check if currently processed array returned sum bigger than the previous one
            // If it was, update information about the biggest maximal sum
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
