#ifndef LAB7_SEARCHING_H
#define LAB7_SEARCHING_H

#include <iostream>
#include <memory>
#include <limits>

namespace searching_element {
    using smart_1D = std::unique_ptr<int[]>;
    using smart_2D = std::unique_ptr<smart_1D[]>;

    enum class MODE {
        FIRST_OCCURRENCE = 1,
        LAST_OCCURRENCE = 2
    };

    /**
     * Structure containing information about element's position in dimensional array
     */
    struct position {
        int row;
        int column;
    };

    /**
     * Structure contains information about dimensional array
     */
    struct array_details {
        int rows;
        int columns;
        smart_2D dimensional_array;
    };

    namespace wrappers {
        /**
         * Wrapper function to search first occurring of value in "recursive mode"
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position recursive_first_occurring(const array_details &arr_det, int searched_value);

        /**
         * Wrapper function to search last occurring of value in "recursive mode"
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position recursive_last_occurring(const array_details &arr_det, int searched_value);

        /**
         * Function to search first occurring of value in "iterative mode"
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position iterative_first_occurring(const array_details &arr_det, int searched_value);

        /**
         * Function to search last occurring of value in "iterative mode"
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position iterative_last_occurring(const array_details &arr_det, int searched_value);
    }

    namespace binary_search {
        /**
         * Binary search implementation to search first occurrence of desired value
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position iterative_first(const array_details &arr_det, int searched_value);

        /**
         * Binary search implementation to search last occurrence of desired value
         * @param arr_det - const reference to structure which contains information about dimensional array
         * @param searched_value - value to search in array
         * @return structure containing information about element's position
         */
        position iterative_last(const array_details &arr_det, int searched_value);

        namespace recursive {
            /**
             * Main caller for recursive binary search
             * @param arr_det - const reference to structure which contains information about dimensional array
             * @param searched_value - value to search in array
             * @param search_mode - enum specifying searching type
             * @return structure containing information about element's position
             */
            position wrapper(const array_details &arr_det, int searched_value, MODE search_mode);

            /**
             * Function "unpacks" next rows and calls binary search for unpacked row in order to find first occurrence
             * of looked value
             * @param arr_det - const reference to structure which contains information about dimensional array
             * @param processed_rows - number of currently processed rows
             * @param searched_value - value to search in array
             * @return structure containing information about element's position
             */
            position unpack_row_first(const array_details &arr_det, int processed_rows, int searched_value);

            /**
             * Function "unpacks" next rows and calls binary search for unpacked row in order to find last occurrence
             * of looked value
             * @param arr_det - const reference to structure which contains information about dimensional array
             * @param processed_rows - number of currently processed rows
             * @param searched_value - value to search in array
             * @return structure containing information about element's position
             */
            position unpack_row_last(const array_details &arr_det, int processed_rows, int searched_value);

            /**
             * Function implements recursive binary searching for single row
             * @param column - row's address (address of first column in row)
             * @param start - sequence's start index (column number)
             * @param end - sequences's end index (column number)
             * @param searched_value - value to search in array
             * @return column number in which element is placed
             */
            int process_row(const int *column, int start, int end, int searched_value);

            /**
             * Function checks if there is no earlier values which are equal to searched value. If they are, the index of
             * searched element is shifted to left
             * @param row - row's address
             * @param column - current column number (searched value position)
             * @param searched_value - value to search in array
             * @return position of the firs occurrence in row
             */
            int check_first(const int *row, int column, int searched_value);

            /**
             * Function checks if there is no later values which are equal to searched value. If they are, the index of
             * searched element is shifted to right
             * @param row - row's address
             * @param column - current column number (searched value position)
             * @param searched_value - value to search in array
             * @return position of the last occurrence in row
             */
            int check_last(const int *row, int column, int searched_value);
        }
    }
}
#endif //LAB7_SEARCHING_H
