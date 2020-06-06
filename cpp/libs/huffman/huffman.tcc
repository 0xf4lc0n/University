#ifndef HUFFMAN_ALGORITHM_HUFFMAN_TCC
#define HUFFMAN_ALGORITHM_HUFFMAN_TCC

#include <iostream>
#include <memory>
#include <initializer_list>
#include <queue>
#include "exceptions.h"
#include "node.tcc"

template<typename T>
class Huffman {
private:
    std::unique_ptr<char[]> _characters;
    std::unique_ptr<T[]> _incidences;
    std::size_t _number_of_elements;
    void _print_codes(Node <T> *root, std::string = "") const;
public:
    Huffman();
    Huffman(int number_of_elements);
    Huffman(std::initializer_list<char> characters, std::initializer_list<T> incidence, int number_of_elements);
    void set_characters(std::initializer_list<char> characters);
    void set_incidences(std::initializer_list<T> incidences);
    void set_amount_of_elements(int number_of_elements);
    void process_algorithm();
    ~Huffman() = default;
};

template<typename T>
Huffman<T>::Huffman() : _incidences(nullptr), _characters(nullptr), _number_of_elements(0) {}


template<typename T>
Huffman<T>::Huffman(int number_of_elements) : _number_of_elements(number_of_elements) {
    _characters = std::make_unique<char[]>(_number_of_elements);
    _incidences = std::make_unique<T[]>(_number_of_elements);
}


template<typename T>
Huffman<T>::Huffman(std::initializer_list<char> characters, std::initializer_list<T> incidence,
                    int number_of_elements) : _number_of_elements(number_of_elements) {
    _characters = std::make_unique<char[]>(_number_of_elements);
    _incidences = std::make_unique<T[]>(_number_of_elements);

    set_characters(characters);
    set_incidences(incidence);
}

template<typename T>
void Huffman<T>::set_characters(std::initializer_list<char> characters) {
    if (characters.size() != _number_of_elements) {
        throw MyExceptions::CustomRunTimeError(
                "Amount of elements is invalid! Update number_of_elements value or provide proper amount of elements!");
    } else {
        std::copy(characters.begin(), characters.end(), _characters.get());
    }
}

template<typename T>
void Huffman<T>::set_incidences(std::initializer_list<T> incidences) {
    if (incidences.size() != _number_of_elements) {
        throw MyExceptions::CustomRunTimeError(
                "Amount of elements is invalid! Update number_of_elements value or provide proper amount of elements!");
    } else {
        std::copy(incidences.begin(), incidences.end(), _incidences.get());
    }
}

template<typename T>
void Huffman<T>::set_amount_of_elements(int number_of_elements) {
    _number_of_elements = number_of_elements;
    _characters = std::make_unique<char[]>(_number_of_elements);
    _incidences = std::make_unique<T[]>(_number_of_elements);

}

template<typename T>
void Huffman<T>::process_algorithm() {
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *top = nullptr;

    std::priority_queue<Node<T> *, std::vector<Node<T> *>, NodeComparator<T>> Heap;

    for (int i = 0; i < _number_of_elements; i++) {
        Heap.push(new Node<T>(_characters[i], _incidences[i]));
    }

    while (Heap.size() != 1) {
        left = Heap.top();
        Heap.pop();

        right = Heap.top();
        Heap.pop();

        top = new Node<T>('/', left->get_incidence() + right->get_incidence());
        top->get_left() = left;
        top->get_right() = right;

        Heap.push(top);
    }
    _print_codes(Heap.top());

    while (Heap.size() != 0) {
        delete Heap.top();
        Heap.pop();
    }
}

template <typename T>
void Huffman<T>::_print_codes(Node <T> *root, std::string str) const {
    if (root) {
        if (root->get_letter() != '/') {
            std::cout << root->get_letter() << ": " << str << std::endl;
        }
        _print_codes(root->get_left(), str + "0");
        _print_codes(root->get_right(), str + "1");
    }
}

#endif //HUFFMAN_ALGORITHM_HUFFMAN_TCC
