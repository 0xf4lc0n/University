#include <iostream>
#include "knapsack.h"

int main(int argc, char *argv[]) {
    knapsack knapsack_alfa{4, 16};

    knapsack_alfa.set_prices({40, 30, 50, 10});
    knapsack_alfa.set_weights({2, 5, 10, 5});

    knapsack_alfa.process_algorithm();
    knapsack_alfa.print_result();

    knapsack_alfa.reset_factors(5, 19);
    knapsack_alfa.set_prices({20, 30, 35, 12, 3});
    knapsack_alfa.set_weights({2, 5, 7, 3, 1});

    knapsack_alfa.process_algorithm();
    knapsack_alfa.print_result();

    return 0;
}
