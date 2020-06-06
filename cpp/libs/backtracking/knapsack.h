#ifndef BACKTRACKING_ALGORITHM_KNAPSACK_H
#define BACKTRACKING_ALGORITHM_KNAPSACK_H

#include <iostream>
#include <memory>
#include <initializer_list>
#include <fstream>
#include <exception>

class knapsack {
    private:
        std::unique_ptr<int[]> _prices;
        std::unique_ptr<int[]> _weights;
        int _number_of_elements;
        int _maximal_weight;
        std::ofstream _debug_file;

        int _maximal_profit = 0;
        int _best_node = 0;
        bool _file_error = false;

        bool is_promising(int i, int weight, int profit);
        void write_node_info(int i, int profit, int weight, bool backtrack_flag = false);
        void write_graph_info();
    public:
        knapsack(int n, int w);

        void set_prices(std::initializer_list<int> p_list);
        void set_weights(std::initializer_list<int> w_list);
        void reset_factors(int n, int w);

        void process_algorithm(int i = 0, int profit = 0, int weight = 0);

        void print_result() const;

        knapsack(const knapsack &) = delete;
        knapsack(knapsack &&) = delete;
        knapsack operator==(const knapsack &) = delete;
        knapsack operator=(knapsack &&) = delete;

        ~knapsack();
};


#endif //BACKTRACKING_ALGORITHM_KNAPSACK_H
