#include "RPN.h"

/*
 * Find operator in maps
 * If operator is left-side r_top_operator will point to r_map.end()
 * Similarly, if operator is right-side l_top_operator will point to r_map.end()
 */
operator_data take_operator(const o_map &l_map, const o_map &r_map, const std::string &c) {
    auto l_top_operator = l_map.find(c);
    auto r_top_operator = r_map.find(c);
    operator_data top_operator{};

    if (l_top_operator != l_map.end()) {
        top_operator.value_weight.first = l_top_operator->first;
        top_operator.value_weight.second = l_top_operator->second;
        top_operator.type = 'l';
    } else if (r_top_operator != r_map.end()) {
        top_operator.value_weight.first = r_top_operator->first;
        top_operator.value_weight.second = r_top_operator->second;
        top_operator.type = 'r';
    }
    return top_operator;
}

std::string to_ONP(const std::string &input, const o_map &l_map, const o_map &r_map) {
    std::string operator_str = "=<>+-*/%^~";
    std::string output;
    std::stack<std::string> stack;
    int operands = 0, operators = 0;

    for (const char &c : input) {
        if (c >= 'a' and c <= 'z') {
            output.append(std::string(1, c));
            operands++;
        } else {
            if (c != '~' and operator_str.find(c) != std::string::npos) {
                operators++;
            }
            if (stack.empty()) {
                stack.push(std::string(1, c));
            } else if (operator_str.find(c) != std::string::npos) {
                operator_data top_operator = take_operator(l_map, r_map, stack.top());
                operator_data current_operator = take_operator(l_map, r_map, std::string(1, c));

                while (((current_operator.type == 'l' and
                         current_operator.value_weight.second <= top_operator.value_weight.second) or
                        (current_operator.type == 'r' and
                         current_operator.value_weight.second < top_operator.value_weight.second)) and not stack.empty()) {
                    output.append(top_operator.value_weight.first);
                    stack.pop();

                    if (not stack.empty()) {
                        top_operator = take_operator(l_map, r_map, stack.top());
                    }
                }
                stack.push(std::string(1, c));
            } else if (c == '(') {
                stack.push(std::string(1, c));
            } else if (c == ')') {
                while (stack.top() != "(") {
                    if (not stack.empty()) {
                        output.append(stack.top());
                        stack.pop();
                    } else {
                        return "error!";
                    }
                }
                stack.pop();
            }
        }
    }

    while (not stack.empty()) {
        if (stack.top() != "(") {
            output.append(stack.top());
            stack.pop();
        } else {
            return "error!";
        }
    }

    if (abs(operands - operators) > 1) {
        return "error!";
    }

    return output;
}

std::string from_ONP(const std::string &input, const o_map &l_map, const o_map &r_map) {
    std::string operator_str = "=<>+-*/%^~";
    std::string output;
    std::string tmp_result;
    std::stack<std::string> stack;
    std::stack<int> priority_stack;
    operator_data current_operator;
    int operators = 0, operands = 0;

    for (const char &c : input) {
        if (c >= 'a' && c <= 'z') {
            stack.push(std::string(1, c));
            priority_stack.push(6);
            operands++;
        } else if (operator_str.find(c) != std::string::npos) {
            if (c != '~') {
                if (stack.empty()) {
                    return "error!";
                }

                operators++;
                tmp_result = "";

                // Download information about operator
                current_operator = take_operator(l_map, r_map, std::string(1, c));

                // Take first operand
                if (priority_stack.top() <= current_operator.value_weight.second) {
                    tmp_result = "(" + stack.top() + ")";
                } else {
                    tmp_result = stack.top();
                }

                stack.pop();
                priority_stack.pop();

                if (stack.empty()) {
                    return "error!";
                }

                // Take second operand
                if (priority_stack.top() < current_operator.value_weight.second) {
                    tmp_result = "(" + stack.top() + ")" + current_operator.value_weight.first + tmp_result;
                } else {
                    tmp_result = stack.top() + current_operator.value_weight.first + tmp_result;
                }

                stack.pop();
                priority_stack.pop();
            } else {
                // Download information about operator
                current_operator = take_operator(l_map, r_map, std::string(1, c));

                // Take operand
                if (priority_stack.top() <= current_operator.value_weight.second) {
                    tmp_result = current_operator.value_weight.first + "(" + stack.top() + ")";
                } else {
                    tmp_result = current_operator.value_weight.first + stack.top();
                }

                stack.pop();
                priority_stack.pop();
            }
            stack.push(tmp_result);
            priority_stack.push(current_operator.value_weight.second);
        }
    }

    output = stack.top();
    stack.pop();

    if (not stack.empty() or operands - 1 != operators) {
        output = "error";
    }

    return output;
}