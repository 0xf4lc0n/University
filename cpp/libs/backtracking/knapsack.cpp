#include "knapsack.h"

knapsack::knapsack(int n, int w) : _number_of_elements(n), _maximal_weight(w) {
    _prices = std::make_unique<int[]>(n);
    _weights = std::make_unique<int[]>(n);
    _debug_file.open("graph_creating_debug.txt", std::ios::out);
    write_graph_info();
}

void knapsack::set_prices(std::initializer_list<int> p_list) {
    if (p_list.size() != _number_of_elements) {
        std::cerr << "You have to type " << _number_of_elements << " prices!" << std::endl;
    } else {
        std::copy(p_list.begin(), p_list.end(), _prices.get());
    }
}

void knapsack::set_weights(std::initializer_list<int> w_list) {
    if (w_list.size() != _number_of_elements) {
        std::cerr << "You have to type " << _number_of_elements << " weights!" << std::endl;
    } else {
        std::copy(w_list.begin(), w_list.end(), _weights.get());
    }
}

void knapsack::reset_factors(int n, int w) {
    _number_of_elements = n;
    _maximal_weight = w;
    _prices = std::make_unique<int[]>(n);
    _weights = std::make_unique<int[]>(n);
    write_graph_info();
}

knapsack::~knapsack() {
    _debug_file.close();
}

bool knapsack::is_promising(int i, int weight, int profit) {
    int j = 0, k = 0;
    int total_weight = 0;
    float bound = 0;

    if (weight >= _maximal_weight) {
        return false;
    } else {
        j = i;
        bound = profit;
        total_weight = weight;
        while (j <= _number_of_elements and total_weight + _weights[j] <= _maximal_weight) {
            total_weight += _weights[j];
            bound += _prices[j];
            j++;
        }
        k = j;
        if (k <= _number_of_elements) {
            bound += (_maximal_weight - total_weight) * _prices[k] / _weights[k];
        }

        return bound > _maximal_profit;
    }
}

void knapsack::process_algorithm(int i, int profit, int weight) {
    write_node_info(i, profit, weight);

    if (weight <= _maximal_weight && profit > _maximal_profit) {
        _maximal_profit = profit;
        _best_node = i;
    }

    if (is_promising(i, weight, profit)) {
        process_algorithm(i + 1, profit + _prices[i], weight + _weights[i]);
        write_node_info(i, profit, weight, true);
        process_algorithm(i + 1, profit, weight);
    }
}

void knapsack::write_node_info(int i, int profit, int weight, bool backtrack_flag) {
    if (_debug_file) {
        if (backtrack_flag) {
            _debug_file << "Backtracking to => i:" << i << " p:" << profit << " w:" << weight << std::endl;
        } else {
            _debug_file << "i:" << i << " p:" << profit << " w:" << weight << std::endl;
        }
    } else {
        _file_error = true;
    }
}

void knapsack::write_graph_info() {
    if (_debug_file) {
        _debug_file << "maximal weight: " << _maximal_weight << " number of elements: "
                    << _number_of_elements << std::endl;
    } else {
        _file_error = true;
    }
}

void knapsack::print_result() const {
    std::cout << "Maximal profit: " << _maximal_profit << std::endl;

    if (_file_error) {
        std::cout << "[Warning] There was a problem during writing to debug files. "
                     "The content of these files may be inappropriate." << std::endl;
    }
}

