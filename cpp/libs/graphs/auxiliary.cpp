#include "auxiliary.h"
#include "../input_sanitization/input_sanitization.tcc"

void download_nodes_and_edges(std::istream &os, std::vector<Edge> &edges_vector, std::set<int> &nodes_set) {
    int n_edges = 0;
    Edge c_edge = {};
    int lines = 1;

    os >> n_edges;
    input_sanitization::check_input(n_edges, os, 0x0L, 0xFFFFFFFFL, lines);

    while (n_edges) {
        lines++;
        os >> c_edge.start_node;
        input_sanitization::check_input(c_edge.start_node, os, 0x0L, 0xFFFFFFFFL, lines);
        os >> c_edge.end_node;
        input_sanitization::check_input(c_edge.end_node, os, 0x0L, 0xFFFFFFFFL, lines);

        nodes_set.insert(c_edge.start_node);
        nodes_set.insert(c_edge.end_node);
        edges_vector.push_back(c_edge);

        n_edges--;
    }
}

void print_neighbours(const std::vector<std::vector<int>> &n_neighbours) {
    for (std::size_t i = 0; i < n_neighbours.size(); i++) {
        std::cout << "Node " << i + 1 << " has " << n_neighbours[i].size() << " neighbours." << std::endl;
        std::cout << "Neighbours: ";
        for (auto &node_mate : n_neighbours[i]) {
            std::cout << node_mate << " ";
        }
        std::cout << std::endl;
    }
}