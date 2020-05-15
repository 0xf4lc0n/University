#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "../libs/input_sanitization/input_sanitization.tcc"
#include "../libs/graphs/auxiliary.h"

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

    if(not input_file.is_open()) {
        std::cout << "File cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    std::set<int> nodes;
    std::vector<Edge> edges;

    download_nodes_and_edges(input_file, edges, nodes);

    auto incidence_matrix = std::make_unique<std::unique_ptr<int[]>[]>(nodes.size());
    std::vector<std::vector<int>> incidence_vector(nodes.size(), std::vector<int>(edges.size(), 0));

    for (std::size_t i = 0; i < nodes.size(); i++) {
        incidence_matrix[i] = std::make_unique<int[]>(edges.size());
    }

    std::vector<std::vector<int>> node_neighbours(nodes.size(), std::vector<int>());
    Edge c_edge = {};

    for (std::size_t i = 0; i < edges.size(); i++) {
        c_edge = edges[i];
        incidence_matrix[c_edge.start_node - 1][i] = 1;
        incidence_matrix[c_edge.end_node - 1][i] = -1;

        incidence_vector[c_edge.start_node - 1][i] = 1;
        incidence_vector[c_edge.end_node - 1][i] = -1;

        node_neighbours[c_edge.start_node - 1].push_back(c_edge.end_node);
        node_neighbours[c_edge.end_node - 1].push_back(c_edge.start_node);
    }

    std::cout << "\"Naked\" 2D array" << std::endl;
    for (std::size_t i = 0; i < nodes.size(); i++) {
        for (std::size_t j = 0; j < edges.size(); j++) {
            std::cout << std::setw(3) << incidence_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Vector 2D array" << std::endl;
    for(const auto & vector : incidence_vector) {
        for (const auto & element : vector) {
            std::cout << std::setw(3) << element << " ";
        }
        std::cout << std::endl;
    }

    print_neighbours(node_neighbours);

    return 0;
}
