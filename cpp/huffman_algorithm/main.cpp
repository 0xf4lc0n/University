#include <iostream>
#include "huffman.tcc"

int main() {
    Huffman<int> huff_alfa{7};
    huff_alfa.set_characters({'A', 'B', 'I', 'M', 'S', 'X', 'Z'});
    huff_alfa.set_incidences({12, 7, 18, 10, 9, 5, 2});
    huff_alfa.process_algorithm();

    std::cout << "###################################" << std::endl;
    Huffman huff_bravo({'c', 'e', 'i', 'r', 's', 't', 'x'}, {0.11, 0.22, 0.16, 0.12, 0.15, 0.10, 0.14}, 7);
    huff_bravo.process_algorithm();

    std::cout << "###################################" << std::endl;
    try {
        Huffman huff_charlie({'a', 'b', 'c', 'd', 'e', 'f'}, {16, 5, 12, 17, 10, 25}, 5);
        huff_charlie.process_algorithm();
    } catch (MyExceptions::CustomRunTimeError &ex) {
        std::cout << "[Error] " << ex.what() << std::endl;
    }

    std::cout << "###################################" << std::endl;
    Huffman huff_charlie({'a', 'b', 'c', 'd', 'e', 'f'}, {16, 5, 12, 17, 10, 25}, 6);
    huff_charlie.process_algorithm();

    std::cout << "###################################" << std::endl;
    Huffman<double> huff_delta;
    huff_delta.set_amount_of_elements(5);
    huff_delta.set_characters({'A', 'B', 'C', 'D', 'E'});
    huff_delta.set_incidences({0.39, 0.21, 0.19, 0.12, 0.09});
    huff_delta.process_algorithm();

    return 0;
}
