#include <iostream>
#include <fstream>

#include "RPN.h"

int main() {
    o_map l_operator_map{
            o_pair("<", 1),
            o_pair(">", 1),
            o_pair("+", 2),
            o_pair("-", 2),
            o_pair("*", 3),
            o_pair("/", 3),
            o_pair("%", 3),
    };

    o_map r_operator_map{
            o_pair("=", 0),
            o_pair("^", 4),
            o_pair("~", 5),
    };

    std::ifstream in_file("in.txt", std::ios::in);
    std::ofstream out_file("out.txt", std::ios::out);

    if (not in_file.is_open()) {
        std::cout << "Input file cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    if (not out_file.is_open()) {
        std::cout << "Output file cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    std::string prefix;
    std::string input;
    std::string output;
    constexpr int max = 0x8000;
    int data_sets;

    in_file >> data_sets;
    std::getline(in_file, input);

    if (data_sets < max) {
        while (data_sets) {
            std::getline(in_file, input);
            prefix = input.substr(0, 3);
            input = input.substr(5, input.length());

            if (prefix == "INF") {
                output = "ONP: " + to_ONP(input, l_operator_map, r_operator_map);
            } else if (prefix == "ONP") {
                output = "INF: " + from_ONP(input, l_operator_map, r_operator_map);
            } else {
                output = "Error! Bad prefix!";
            }

            out_file << output << std::endl;
            data_sets--;
        }
    } else {
        out_file << "To many data sets!" << std::endl;
    }

    in_file.close();
    out_file.close();
}
