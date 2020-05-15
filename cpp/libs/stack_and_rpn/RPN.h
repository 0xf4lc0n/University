#ifndef LAB4_ONP_H
#define LAB4_ONP_H

#include <stack>
#include <string>
#include <map>

using o_map = std::map<std::string, int>;
using o_pair = std::pair<std::string, int>;

/**
 * Structure contains data about operators
 * value_weight contains operator character (char) and priority (int)
 * type - type of associativity (l - left-side, r - right-side)
 */
struct operator_data {
    std::pair<std::string, int> value_weight;
    char type;
};

/**
 * Function returns structure which represents operator on the stack's _top
 * @param l_map - map of left associative operators
 * @param r_map - map of right associative operators
 * @param c - operator stack
 * @return structure which represents operator on the stack
 */
operator_data take_operator(const o_map &l_map, const o_map &r_map, const std::string &c);

/**
 * Functions converts expression from INF to ONP form
 * @param input - expression in INF form
 * @param l_map - map of left associative operators
 * @param r_map - map of right associative operators
 * @return expression in ONP form
 */
std::string to_ONP(const std::string &input, const o_map &l_map, const o_map &r_map);


/**
 * Functions converts expression from ONP to INF form
 * @param input - expression in INF form
 * @param l_map - map of left associative operators
 * @param r_map - map of right associative operators
 * @return expression in INF form
 */
std::string from_ONP(const std::string &input, const o_map &l_map, const o_map &r_map);

#endif //LAB4_ONP_H
