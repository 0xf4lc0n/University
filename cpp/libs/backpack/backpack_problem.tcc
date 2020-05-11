#ifndef LAB9_BACKPACK_PROBLEM_TCC
#define LAB9_BACKPACK_PROBLEM_TCC

#include <memory>
#include <iomanip>
#include <iostream>
#include <vector>
#include "subject.tcc"

namespace display {
    template<typename T>
    using matrix = std::unique_ptr<std::unique_ptr<T[]>[]>;

    /**
     * Function display 2D array in
     * @tparam T - type value
     * @param mtr - two dimensional array in a tabular manner
     * @param x - number of columns
     * @param y - number of rows
     */
    template<typename T>
    void result_matrix(const matrix<T> &mtr, std::size_t x, std::size_t y) {
        for (std::size_t i = 0; i < y; i++) {
            for (std::size_t j = 0; j < x; j++) {
                std::cout << std::setw(3) << mtr[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

namespace recursive {
    namespace internal_implementations {
        /**
         * Function deletes elements until desired value occurred
         * @tparam T - value type
         * @param result - vector stores a sequence that completely fills the backpack
         * @param target_value - desired value which must stay in sequence (must be unique)
         */
        template<typename T>
        void _delete_subsequence(std::vector<T> &result, const T & target_value) {
            if (result.back() != target_value) {
                result.pop_back();
                _delete_subsequence(result, target_value);
            }
        }

        /**
         * Recursive algorithm packing backpack to it's bounds
         * @tparam T - value type
         * @param source - vector contains all weights
         * @param m_start - start index of main sequence
         * @param s_start - start index of currently processed subsequence
         * @param c_index - index of currently processed element
         * @param c_weight - current weight
         * @param t_weight - target weight (maximal backpack's capacity)
         * @param result - vector stores a sequence that completely fills the backpack
         */
        template<typename T>
        void _pack_backpack(const std::vector<T> &source, int m_start, int s_start, int c_index,
                            T &c_weight, T t_weight, std::vector<T> &result) {
            c_weight += source[c_index];
            result.push_back(source[c_index]);

            if (m_start < source.size()) {
                if (c_weight < t_weight and c_index < source.size()) {
                    _pack_backpack(source, m_start, s_start, c_index + 1, c_weight, t_weight, result);
                }

                if (c_weight > t_weight and c_index < source.size()) {
                    c_weight -= source[c_index];
                    result.pop_back();
                    _pack_backpack(source, m_start, s_start, c_index + 1, c_weight, t_weight, result);
                }

                if (c_index == source.size() - 1 and c_weight != t_weight) {
                    c_weight = source[m_start];
                    _delete_subsequence(result, c_weight);
                    _pack_backpack(source, m_start, s_start + 2, s_start + 2, c_weight,
                                   t_weight, result);
                }

                if (s_start >= source.size() and c_weight != t_weight) {
                    result.clear();
                    c_weight = 0;
                    _pack_backpack(source, m_start + 1, m_start + 1, m_start + 1, c_weight, t_weight, result);
                }
            }
        }
    }

    /**
     * Wrapper for recursive packing backpack function
     * @tparam T - value type
     * @param source - vector contains all weights
     * @param target_weight - target weight (maximal backpack's capacity)
     * @return vector of weights which completely fills the backpack or empty vector if such sequence doesn't exist
     */
    template<typename T>
    std::vector<T> pack_backpack(const std::vector<T> &source, int target_weight) {
        std::vector<T> result;
        T current_weight = 0;

        internal_implementations::_pack_backpack(source, 0, 0, 0, current_weight, target_weight, result);
        if (current_weight == target_weight) {
            return result;
        } else {
            return {};
        }
    }

}


#endif //LAB9_BACKPACK_PROBLEM_TCC
