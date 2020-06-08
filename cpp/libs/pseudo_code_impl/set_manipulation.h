#ifndef LAB3_SET_MANIPULATION_H
#define LAB3_SET_MANIPULATION_H

#include <iostream>
#include <memory>
#include <vector>
#include "input_sanitization.tcc"

/**
 * Functions sends created set for designated output
 * @param n_set number set, which represent the logical chassis of printing
 * @param c_set char set, which contains chars to print
 * @param size size of set
 * @param os output stream
 */
void print_set(const std::unique_ptr<int[]> &n_set, const std::unique_ptr<char[]> &c_set, std::size_t size,
               std::ostream &os);

/**
 * Function sends created set for designated output
 * Used for printing sets in lexicographical order
 * @param n_set number set, which represent the logical chassis of printing
 * @param c_set char set, which contains chars to print
 * @param subset_size size of subset
 * @param os output stream
 */
void print_set_lg(const std::unique_ptr<int[]> &n_set, const std::unique_ptr<char[]> &c_set, std::size_t subset_size,
                  std::ostream &os);

/**
 * Function fills char array chars (starting from A)
 * @param c_set array to represent char set
 * @param size size of char array
 */
void fill_char_set(std::unique_ptr<char[]> &c_set, std::size_t size);

/**
 * Function sends pretty result on output
 * @param distributed_numbers vector which contains distributed numbers
 * @param amount_of_numbers vector which contains amount of each factor
 * @param primary_number basic number before distribution
 * @param os output stream
 */
void print_factor_array(std::vector<int> &distributed_numbers, std::vector<int> &amount_of_numbers, int primary_number,
                        std::ostream &os);

/**
 * Function assigns and check set's size value
 * @tparam T - value type
 * @param set_type - string specifies if it is set or subset
 * @param size_variable - reference to variable storing structure size
 */
template<typename T>
void input_number_of_elements(const std::string &set_type, T &size_variable) {
    std::cout << "Number of " << set_type << " elements: ";
    std::cin >> size_variable;
    input_sanitization::check_input(size_variable, std::cin, 1, 26);
}

#endif //LAB3_SET_MANIPULATION_H