#ifndef SORT_ALGORITHMS_C_SORT_ARRAY_H
#define SORT_ALGORITHMS_C_SORT_ARRAY_H

#include <memory>
#include <initializer_list>
#include <random>
#include <algorithm>
#include "exceptions.h"
#include "input_sanitization.tcc"

namespace isa = input_sanitization;

template<typename T>
class CSortArray {
private:
    std::size_t _number_of_elements;
protected:
    std::unique_ptr<T[]> _value_array;
public:
    CSortArray();

    CSortArray(int size);

    CSortArray(int size, std::initializer_list<T> values);

    CSortArray(const CSortArray<T> &cst);

    /**
     * Method allows for inserting values from standard input
     */
    void insert_values();

    /**
     * Method fills internal array with values form specified range
     * @param min_number - start of the range
     * @param max_number - end of the range
     */
    void generate_values(long min_number = 0x1, long max_number = 0xFFF);

    /**
     * Method reverses array
     */
    void reverse();

    /**
     * Method provides partial order in sorted array
     * @param randomness_factor - specifies how many values should be swapped (in %)
     */
    void randomize(double randomness_factor);

    void set_size(int size);

    inline std::size_t get_size() const { return _number_of_elements; }

    T &operator[](std::size_t index) { return _value_array[index]; }

    CSortArray &operator=(const CSortArray<T> &cst) = delete;

    virtual ~CSortArray() = default;
};

template<typename T>
CSortArray<T>::CSortArray() : _value_array(nullptr), _number_of_elements(0) {}

template<typename T>
CSortArray<T>::CSortArray(int size) : _number_of_elements(size) {
    _value_array = std::make_unique<T[]>(size);
}

template<typename T>
CSortArray<T>::CSortArray(int size, std::initializer_list<T> values) : _number_of_elements(size) {
    _value_array = std::make_unique<T[]>(size);

    if (_number_of_elements != values.size()) {
        throw MyExceptions::CustomRunTimeError(
                "Amount of elements is invalid! Update number_of_elements value or provide proper amount of elements!");
    } else {
        std::copy(values.begin(), values.end(), _value_array.get());
    }
}

template<typename T>
CSortArray<T>::CSortArray(const CSortArray<T> &cst) {

    _number_of_elements = cst._number_of_elements;
    _value_array = std::make_unique<T[]>(_number_of_elements);

    for (std::size_t i = 0; i < _number_of_elements; i++) {
        _value_array[i] = cst._value_array[i];
    }

}

template<typename T>
void CSortArray<T>::insert_values() {
    if (_number_of_elements != 0 and _value_array != nullptr) {
        for (std::size_t i = 0; i < _number_of_elements; i++) {
            std::cin >> _value_array[i];
            isa::check_input(_value_array[i]);
        }
    } else {
        throw MyExceptions::CustomRunTimeError(
                "Amount of elements is invalid! Update number_of_elements value or provide proper amount of elements!");
    }
}

template<typename T>
void CSortArray<T>::set_size(int size) {
    _number_of_elements = size;
    _value_array = std::make_unique<T[]>(size);
}

template<typename T>
void CSortArray<T>::generate_values(long min_number, long max_number) {
    if (_number_of_elements != 0 and _value_array != nullptr) {
        std::random_device r_dev;
        std::mt19937_64 rng(r_dev());
        std::uniform_int_distribution<long> u_int_dist(min_number, max_number);

        for (std::size_t i = 0; i < _number_of_elements; i++) {
            _value_array[i] = u_int_dist(rng);
        }
    } else {
        throw MyExceptions::CustomRunTimeError(
                "Amount of elements is invalid! Update number_of_elements value or provide proper amount of elements!");
    }
}

template<typename T>
void CSortArray<T>::reverse() {
    std::reverse(_value_array.get(), _value_array.get() + _number_of_elements);
}

template<typename T>
void CSortArray<T>::randomize(double randomness_factor) {
    int amount_of_swaps = _number_of_elements * randomness_factor / 200;
    std::random_device r_dev;
    std::mt19937_64 rng(r_dev());
    std::uniform_int_distribution<long> u_int_dist(0, _number_of_elements - 1);
    int first_element_index = 0;
    int second_element_index = 0;

    while (amount_of_swaps != 0) {
        first_element_index = u_int_dist(rng);
        second_element_index = u_int_dist(rng);
        std::swap(_value_array[first_element_index], _value_array[second_element_index]);
        amount_of_swaps--;
    }
}

#endif //SORT_ALGORITHMS_C_SORT_ARRAY_H
