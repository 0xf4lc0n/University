#ifndef SORT_ALGORITHMS_STACK_SIZE_H
#define SORT_ALGORITHMS_STACK_SIZE_H
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
    constexpr bool is_linux = false;
#else
    #define IS_LINUX
    #include <sys/resource.h>
    constexpr bool is_linux = true;
     /**
     * Function sets stack size for process
     * @param size - new stack size
     */
    void change_stack_size(int size = 8);
#endif  // OS Check

#endif //SORT_ALGORITHMS_STACK_SIZE_H
