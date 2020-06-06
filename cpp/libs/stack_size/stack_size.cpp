#include "stack_size.h"

#ifdef IS_LINUX
void change_stack_size(int size) {
    // Set stack size
    // 8 MB
    const rlim_t stack_size = 8 * 1024 * 1024;
    struct rlimit rl;
    // Download current configuration
    int err_code = getrlimit(RLIMIT_STACK, &rl);

    if (err_code == 0) {
        // Set new stack size
        rl.rlim_cur = stack_size;
        err_code = setrlimit(RLIMIT_STACK, &rl);

        if (err_code != 0) {
            std::cerr << "setrlimit error code: " << err_code << std::endl;
            exit(EXIT_FAILURE);
        }

    } else {
        std::cerr << "Set size cannot be modified!" << std::endl;
        std::cerr << "Due to this issue quciksort called for ordered set of data will cause stack overflow!"
                  << std::endl;
        std::cerr << "Aborting..." << std::endl;
        exit(EXIT_FAILURE);
    }
}
#endif