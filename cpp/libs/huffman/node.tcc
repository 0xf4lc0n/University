#ifndef HUFFMAN_ALGORITHM_NODE_TCC
#define HUFFMAN_ALGORITHM_NODE_TCC

template<typename T>
class Node {
private:
    char _letter;
    T _incidence;
    Node *_left;
    Node *_right;
public:
    Node();
    Node(char letter, T incidence);
    inline void set_letter(char letter) { _letter = letter; }
    inline void set_incidence(int incidence) { _incidence = incidence; }
    inline Node *& get_left() { return _left; }
    inline Node *& get_right() { return _right; }
    [[nodiscard]] inline const T & get_incidence() const { return _incidence; }
    [[nodiscard]] inline const char & get_letter() const { return _letter; }
    ~Node();
};

template <typename T>
class NodeComparator {
public:
    NodeComparator() = default;
    bool operator()(const Node<T> *n1, const Node<T> *n2) { return (n1->get_incidence() > n2->get_incidence()); }
    ~NodeComparator() = default;
};

template<typename T>
Node<T>::Node() : _letter('\0'), _incidence(0), _left(nullptr), _right(nullptr) {}

template<typename T>
Node<T>::Node(char letter, T incidence) : _letter(letter), _incidence(incidence), _left(nullptr), _right(nullptr) {}

template<typename T>
Node<T>::~Node() {
    delete _left;
    delete _right;
}

#endif //HUFFMAN_ALGORITHM_NODE_TCC
