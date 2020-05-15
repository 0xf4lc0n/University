#ifndef LAB2_AWESOME_CUT_LIBRARY_H
#define LAB2_AWESOME_CUT_LIBRARY_H

#include "iostream"
#include <vector>

namespace recursion {
    namespace wrappers {
        /**
         * Function calculates polynomial
         * @param n - size of array decreased by one which contains polynomial components
         * @param a - array containing polynomial components
         * @param x - const component
         * @return value onf polynomial
         */
        int f_wielomian(int n, const int *a, int x);

        /**
         * Function returns address of the biggest element in array
         * @param N - size of array
         * @param t - address of array
         * @return address of the biggest element
         */
        const int *f_maximum(int N, const int *t);

        /**
         * Function calculates Newton symbol
         * @param N - first component of Newton symbol
         * @param K - second component of Newton symbol
         * @return value of Newton symbol
         */
        int f_newton(int N, int K);

        /**
         * Function calculates conditional average for all elements in sequence which fulfil condition
         * @param s - variable which will store result of average
         * @param f - function which checks condition
         * @param b - start address of sequence
         * @param e - end address of sequence
         * @return average of elements which fulfil condition
         */
        unsigned int f_srednia_warunkowa(double &s, bool (*f)(int), const int *b, const int *e);

        /**
         * Function calculates sum all elements in sequence which are positive. Also sum of weights must be
         * smaller than 1
         * @param s - variable which will store result of sum
         * @param b - start address of weight sequence
         * @param e - end address of weight sequence
         * @param a - start of sum components sequence
         * @return weighted sum
         */
        bool f_suma_wazona(double &s, const double *b, const double *e, const double *a);
    }

    namespace auxiliary {
        /**
         * Functions calculates a power
         * @param x - base
         * @param y - exponent
         * @return x raised to the power of y
         */
        int pow(int x, int y);

        /**
         * Function checks if all values in array are greater or equal to 0
         * @param b - start address
         * @param e - end address
         * @return true if all values are positive otherwise false
         */
        bool is_positive(const double *b, const double *e);

        /**
         * Function calculate sum of elements in sequence (e.g. array)
         * @param b - start address
         * @param e - end address
         * @return sum of elements in sequence
         */
        double sum(const double *b, const double *e);

        /**
         * Function calculate sum for all elements in sequence (e.g. array) which fulfil condition checked in function
         * passed as argument. For this elements function returns true
         * @param b - start address
         * @param e - end address
         * @param f - pointer to function which return bool value and take as argument one integer value
         * @return sum of elements which fulfil condition
         */
        int conditional_sum(const int *b, const int *e, bool (*f)(int));

        /**
         * Function calculates weighted sum
         * @param b - start address of weight values
         * @param e - end address of weight values
         * @param a - start address of sum components
         * @return - weighted sum for elements which have their weights
         */
        double weighted_sum(const double *b, const double *e, const double *a);

        /**
         * Return value of last element in a sequence
         * @param b - start address of weight values
         * @param e - end address of weight values
         * @param a - start address of sum components
         * @return value of last element in a sequence
         */
        double last_element(const double *b, const double *e, const double *a);

        /**
         * Returns number of elements which fulfill condition checked in function
         * passed as argument. For this elements function returns true
         * @param b - start address
         * @param e - end address
         * @param f - pointer to function which return bool value and take as argument one integer value
         * @return number of elements which fulfill condition
         */
        int valid_elements(const int *b, const int *e, bool (*f)(int));

        /**
         * Function checks if number is not equal to zero
         * @param x - number to check
         * @return true if number is different from zero otherwise false
         */
        inline bool TRUE(int x) {
            return x != 0;
        }

        /**
         * Function checks if number is equal to zero
         * @param x - number to check
         * @return true if number is equal to zero otherwise false
         */
        inline bool FALSE(int x) {
            return x == 0;
        }

        /**
         * Function return bigger value
         * @tparam T - type of variables
         * @param a - first value
         * @param b - second value
         * @return
         */
        template<typename T>
        const T &max(const T &a, const T &b) {
            return (a < b) ? b : a;
        }
    }
}

namespace merge {
    /**
     * Splits array to two arrays if array have more than one element, and then call merge_array fuction
     * @param num_array - array with numbers to examine
     * @param temp - auxiliary array
     * @param start_index - start index of num_array
     * @param end_index - end index of end_array
     * @return number or inversions
     */
    int merge_sort(std::vector<int> &num_array, std::vector<int> &temp, int start_index,
                   int end_index);

    /**
     * Function counts inversions and creates sorted array
     * @param num_array - array with numbers to examine
     * @param temp - auxiliary array
     * @param start_index - start index of num_array
     * @param middle_index - middle index of num_array
     * @param end_index - end index of end_array
     * @return number or inversions
     */
    int
    merge_arrays(std::vector<int> &num_array, std::vector<int> &temp, int start_index, int middle_index, int end_index);
}
#endif //LAB2_AWESOME_CUT_LIBRARY_H
