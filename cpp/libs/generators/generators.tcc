#ifndef LAB8_GENERATORS_TCC
#define LAB8_GENERATORS_TCC

#include <iostream>
#include <random>

/**
 * Function generates pseudo random number
 * @tparam T - variable type
 * @param min_number - universal reference to start of the range
 * @param max_number - universal reference to end of the range
 * @return pseudo random number
 */
template<typename T>
T random_number_generator(T &&min_number = 0x1L, T &&max_number = 0xFFFFFFFF) {
    std::random_device r_dev;
    std::mt19937_64 rng(r_dev());
    std::uniform_int_distribution<T> u_int_dist(min_number, max_number);

    return u_int_dist(rng);
}

/**
 * Function calculates the greatest common divisor of two numbers
 * @tparam T - variable type
 * @param a - first number
 * @param b - second number
 * @return - greatest common divisor of two numbers
 */
template<typename T>
decltype(auto) GCD(T a, T b) {
    T tmp = 0;

    while (b != 0) {
        tmp = b;
        b = a % b;
        a = tmp;
    }

    return a;
}

/**
 * Class which implements linear congruential generator
 * @tparam T - factors' and generated numbers' type
 */
template<typename T>
class LCG {
private:
    std::vector<T> _number_container;
    T _increase;
    T _multiplier;
    T _module;

    /**
     * Wrapper method which sets factors and calculate the first pseudo random number
     * If seed is default function calculate it
     * @param m - module
     * @param seed - seed for generator
     */
    void _set_factors(T m, T seed);

    /**
     * Method calculates and sets increase factor
     */
    void _set_increase();

    /**
     * Method calculates and sets multiplier factor
     */
    void _set_multiplier();

public:
    /**
     * Constructor
     * If called with default arguments, calling reset method is not necessary
     * @param m - module
     * @param seed - seed for generator
     */
    explicit LCG(T m = 10, T seed = -1);

    /**
     * Method generates pseudo random numbers
     * @param amount - amount of numbers to generate
     */
    void generate_numbers(std::size_t amount);

    /**
     * Function displays factors
     */
    void show_factors(std::ostream &os = std::cout) const;

    /**
     * Method resets all factors and internal vectors which store generated numbers
     * @param m - new module
     * @param seed - new sed
     */
    void reset(T m, T seed);

    /**
     * Method moves internal vector array to caller
     * After using this method it is necessary to call reset method
     * @return
     */
    std::vector<T> &&get_vector();

    /**
     * Friend function which sends generated numbers to output
     * @tparam U - generator type
     * @param os - reference to output stream
     * @param g - reference to const gererator object
     * @return - reference to output strem
     */
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const LCG<U> &g);
};

template<typename T>
LCG<T>::LCG(T m, T seed) {
    _set_factors(m, seed);
}

template<typename T>
void LCG<T>::_set_factors(T m, T seed) {
    _module = m + 1;
    _multiplier = 1;
    _increase = 0;

    _set_increase();
    _set_multiplier();

    if (seed == -1) {
        seed = random_number_generator<long>();
    }
    _number_container.emplace_back((_multiplier * seed + _increase) % _module);
}

template<typename T>
void LCG<T>::_set_increase() {
    do _increase = random_number_generator<long>() % _module; while (GCD(_module, _increase) != 1);
}

template<typename T>
void LCG<T>::_set_multiplier() {
    T divisor = 2;
    T module_sqrt = T(std::sqrt(_module));
    T module_copy = _module;

    while (divisor <= module_sqrt) {
        while (module_copy % divisor == 0) {
            _multiplier *= divisor;
            module_copy /= divisor;
        }
        divisor++;
    }

    _multiplier++;
}

template<typename T>
void LCG<T>::generate_numbers(std::size_t amount) {
    while (_number_container.size() != amount) {
        _number_container.emplace_back((_multiplier * _number_container.back() + _increase) % _module);
    }
}

template<typename T>
void LCG<T>::reset(T m, T seed) {
    _number_container.clear();
    _set_factors(m, seed);
}

template<typename T>
void LCG<T>::show_factors(std::ostream &os) const {
    os << "a: " << _multiplier
       << " c: " << _increase
       << " m: " << _module << std::endl;
}

template<typename T>
std::vector<T> &&LCG<T>::get_vector() {
    return std::move(_number_container);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const LCG<U> &g) {
    for (const auto &e : g._number_container) {
        os << e << "\n";
    }
    return os;
}

template<typename T>
class ACG {
private:
    std::vector<T> _number_array;
    std::vector<T> _reverse_number_array;
    int _k{}, _j{};
    T _module;
    std::size_t _array_size{};

    /**
     * Method which uses LCG to fill internal vectors
     * @param n - size of internal vector
     */
    void _fill_array(int n);

    /**
     * Wrapper method which sets factors and calculate the first pseudo random number
     * If seed is default function calculate it
     * @param n - number of numbers to generate
     * @param m - module factor
     * @param j - first number from pair
     * @param k - second number from pair
     */
    void _set_factors(int n, T m, int j, int k);

public:
    /**
     * Default constructor
     * If object is created by this constructor it's necessary to use reset method in order to set factors and vectors
     */
    explicit ACG() = default;

    /**
     * Constructor
     * @param n - number of numbers to generate
     * @param m - module factor
     * @param j - first number from pair
     * @param k - second number from pair
     */
    ACG(int n, T m, int j, int k);

    /**
     * Method generates pseudo random numbers
     */
    void generate_numbers();

    /**
     * Method resets all factors and internal vectors which store generated numbers
     * @param n - new number of numbers to generate
     * @param m - new factor
     * @param j - new first number from pair
     * @param k - new second number from pair
     */
    void reset(int n, T m, int j, int k);

    /**
     * Friend function which sends generated numbers to output
     * @tparam U - generator type
     * @param os - reference to output stream
     * @param g - reference to const generator object
     * @return - reference to output stream
     */
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const ACG<U> &g);
};

template<typename T>
ACG<T>::ACG(int n, T m, int j, int k) {
    _set_factors(n, m, j, k);
    _fill_array(n);
}

template<typename T>
void ACG<T>::_fill_array(int n) {
    LCG number_generator(long(20), long(40));
    number_generator.generate_numbers(n);

    _number_array = number_generator.get_vector();
    _reverse_number_array.resize(n, 0);
    std::copy(_number_array.rbegin(), _number_array.rend(), _reverse_number_array.begin());
}

template<typename T>
void ACG<T>::_set_factors(int n, T m, int j, int k) {
    _array_size = n - 1;
    _k = k - 1;
    _j = j - 1;
    _module = m;
}

template<typename T>
void ACG<T>::generate_numbers() {
    int k = _k, j = _j;
    for (std::size_t i = 0; i < _array_size; i++) {

        _reverse_number_array[k] = (_reverse_number_array[j] + _reverse_number_array[k]) % _module;
        k--;
        j--;

        if (k < 0) k = _array_size;
        else if (j < 0) j = _array_size;
    }
}

template<typename T>
void ACG<T>::reset(int n, T m, int j, int k) {
    _number_array.clear();
    _reverse_number_array.clear();
    _set_factors(n, m, j, k);
    _fill_array(n);
}

template<typename U>
std::ostream &operator<<(std::ostream &os, const ACG<U> &g) {
    for (const auto &e : g._reverse_number_array) {
        os << e << "\n";
    }
    return os;
}

#endif //LAB8_GENERATORS_TCC
