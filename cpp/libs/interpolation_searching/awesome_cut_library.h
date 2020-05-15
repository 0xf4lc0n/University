#ifndef LAB2_AWESOME_CUT_LIBRARY_H
#define LAB2_AWESOME_CUT_LIBRARY_H

#include <iostream>
#include <fstream>
#include <random>
#include <numeric>
#include <vector>
#include <algorithm>
#include <set>

constexpr int MAX_DATA_SETS = 0x8000;
constexpr long MAX_NUMBER = 0x1000000000000;

template<typename T>
struct output_file_data {
    std::string file_name;
    std::size_t number_of_data_sets;
    T max_number;
    T min_number;

    output_file_data() : file_name(""), number_of_data_sets(0), max_number(0), min_number(0) {}

    output_file_data(std::string &&fn, std::size_t nods, T min, T max) : file_name(fn), number_of_data_sets(nods),
                                                                         max_number(max), min_number(min) {}
};

/**
 * Function creates file for results of searching
 * @param file_name - name of the output file
 * @return ofstream object, by move semantics
 */
std::ofstream create_result_file(const std::string & file_name);

/**
 * Interpolation search algorithm
 * @param vec - non-decreasingly sorted std::vector with numbers
 * @param searching_value - number sought
 * @return index of the first occurrence of the number sought
 */
int interpolation_search(std::vector<int> & vec, int searching_value);

/**
 * Function calculate amount of the same numbers in vector
 * @param vec - non-decreasingly sorted std::vector with numbers
 * @param index - index of the first occurrence of the number in std::vector
 * @param number - sought number
 * @return amount of the same numbers in vector
 */
int calculate_equal_numbers(std::vector<int> & vec, int index, int number);

/**
 * Function downloads data from file, performs interpolation search, removes duplicates and produces the output
 * @param file_name - name of the file with data to examine
 * @return true if it succeeds, otherwise false
 */
bool load_data_from_file(const std::string &file_name);

#endif //LAB2_AWESOME_CUT_LIBRARY_H
