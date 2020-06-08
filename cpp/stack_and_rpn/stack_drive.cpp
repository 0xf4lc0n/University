#include <iostream>
#include "Stack.tcc"
#include "input_sanitization.tcc"

namespace ins = input_sanitization;

int main() {
    std::ifstream in_file;

    in_file.open("stack_input.txt", std::ios::in);

    if (not in_file.is_open()) {
        std::cout << "Error! File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    int stack_size = 0;
    int number = 0;

    in_file >> stack_size;
    ins::check_input(stack_size, in_file);

    Array::Stack<int> array_stack(stack_size);
    List::Stack<int> list_stack(stack_size);
    std::stack<int> std_stack;
    std::stringstream as, ls, ss;

    for (std::size_t i = 0; i < stack_size; i++) {
        in_file >> number;
        ins::check_input(number, in_file);

        array_stack.push(number);
        list_stack.push(number);
        std_stack.push(number);
    }

    in_file.close();

    int as_r, ls_r;

    for(std::size_t i = 0; i < stack_size; i++) {
        array_stack.pop(as_r);
        list_stack.pop(ls_r);
        as << as_r << " ";
        ls << ls_r << " ";
        ss << std_stack.top() << " ";
        std_stack.pop();
    }

    std::cout << as.str() << std::endl;
    std::cout << ls.str() << std::endl;
    std::cout << ss.str() << std::endl;

    return 0;
}
