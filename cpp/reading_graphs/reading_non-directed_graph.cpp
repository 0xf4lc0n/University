#include <iostream>
#include <fstream>
#include <string>

#include "../libs/graphs/auxiliary.h"
#include "../libs/input_sanitization/input_sanitization.tcc"

using List = class_example::List;
namespace isn = input_sanitization;

int main() {
    std::ifstream input_file;
    std::string file_name;

    std::cout << "Name of the input file [file extension may be omitted]: ";
    std::cin >> file_name;

    while(not isn::is_file_extension_valid(file_name)) {
        std::cout << "Program supports only txt files!" << std::endl;
        std::cout << ">> ";
        std::cin >> file_name;
    }

    input_file.open(file_name, std::ios::in);

    if (not input_file.is_open()) {
        std::cout << "File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    std::set<int> nodes;
    std::vector<Edge> edges;

    download_nodes_and_edges(input_file, edges, nodes);

    auto incidence_lists_array = std::make_unique<List[]>(nodes.size());
    std::vector<std::vector<int>> node_neighbours(nodes.size(), std::vector<int>());
    Edge c_edge = {};

    for (auto edge : edges) {
        c_edge = edge;
        incidence_lists_array[c_edge.start_node - 1].push_back(c_edge.end_node);
        incidence_lists_array[c_edge.end_node - 1].push_back(c_edge.start_node);
        node_neighbours[c_edge.start_node - 1].push_back(c_edge.end_node);
        node_neighbours[c_edge.end_node - 1].push_back(c_edge.start_node);
    }

    for (std::size_t i = 0; i < nodes.size(); i++) {
        std::cout << i + 1 << ": " << incidence_lists_array[i] << std::endl;
    }

    print_nodes_factors(incidence_lists_array, nodes.size());

    return 0;
}
