#ifndef LAB6_AUXILIARY_H
#define LAB6_AUXILIARY_H

#include "List.h"

/**
 * Function prints neighbours for all nodes
 * @param vec - vector which stores information about nodes' neighbours
 */
void print_neighbours(const std::vector<std::vector<int>> &vec);


/**
 * Function downloads informations about edges and nodes from specified input streams
 * @param os - input stream
 * @param edges_vector - vector which stores edges
 * @param nodes_set - set which stores nodes
 */
void download_nodes_and_edges(std::istream &os, std::vector<Edge> &edges_vector, std::set<int> &nodes_set);

/**
 *  Function prints factors for each node in undirected graph
 * @tparam T - List type
 * @param incidence_list_array - Array of incidence lists
 * @param size - size of incidence_list_array
 */
template <typename T>
void print_nodes_factors(const std::unique_ptr<T> &incidence_list_array, std::size_t size) {
    for (std::size_t i = 0; i < size; i++) {
        std::cout << i + 1 << " node factor: " << incidence_list_array[i].number_of_elements() << std::endl;
    }
}

#endif //LAB6_AUXILIARY_H
