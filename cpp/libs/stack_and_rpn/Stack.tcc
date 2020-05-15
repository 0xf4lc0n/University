#ifndef LAB4_STACK_TCC
#define LAB4_STACK_TCC

#include <iostream>
#include <memory>
#include <stack>
#include <fstream>
#include <sstream>

namespace Array {
    template<typename T>
    class Stack {
    private:
        std::unique_ptr<T> _stack_array;
        std::size_t _top;
        std::size_t _size;
    public:
        explicit Stack(std::size_t n = 5);
        Stack(const Stack &st);
        Stack(Stack &&st) noexcept;
        ~Stack() = default;
        bool push(const T &element);
        bool pop(T &element);
        [[nodiscard]] std::size_t number_of_elements() const;
        [[nodiscard]] bool is_full() const ;
        [[nodiscard]] bool is_empty() const;
        Stack &operator=(const Stack &st);
        Stack &operator=(Stack &&st) noexcept;
    };
}

namespace List {
    template <typename T>
    struct Node {
        T item;
        std::shared_ptr<Node<T>> next_item;
    };

    template <typename T>
    class Stack {
        private:
            std::shared_ptr<Node<T>> _front;
            std::shared_ptr<Node<T>> _rear;
            std::size_t _size;
            std::size_t _items;
        public:
            explicit Stack(std::size_t n = 5);
            Stack(const Stack &st) = delete;
            Stack(Stack &&st) noexcept;
            ~Stack() = default;
            bool push(const T &element);
            bool pop(T &element);
            [[nodiscard]] std::size_t number_of_elements() const;
            [[nodiscard]] bool is_full() const ;
            [[nodiscard]] bool is_empty() const;
            Stack &operator=(const Stack &st) = delete;
            Stack &operator=(Stack &&st) noexcept;
    };
}

template <typename T>
List::Stack<T>::Stack(std::size_t n) {
    _front = nullptr;
    _rear = nullptr;
    _size = n;
    _items = 0;
}

template <typename T>
List::Stack<T>::Stack(Stack<T> &&st) noexcept {
    _front = std::move(st._front);
    st._front = nullptr;
    _rear = std::move(st._rear);
    st._rear = nullptr;
    _size = st._size;
    _items = st._items;
}

template <typename T>
bool List::Stack<T>::push(const T &element) {
    if (is_full()) {
        return false;
    }

    std::shared_ptr<Node<T>> new_element(new Node<T>);
    new_element->item = element;
    new_element->next_item = nullptr;
    _items++;

    if (_front == nullptr) {
        _front = new_element;
    } else {
        _rear->next_item = new_element;
    }

    _rear = new_element;

    return true;
}

template <typename T>
bool List::Stack<T>::pop(T &element) {
    if (_front == nullptr) {
        return false;
    }

    element = _front->item;
    _items--;

    std::shared_ptr<Node<T>> temp = _front;
    _front = _front->next_item;

    if (_items == 0) {
        _rear = nullptr;
    }

    return true;
}

template <typename T>
std::size_t List::Stack<T>::number_of_elements() const {
    return _items;
}

template <typename T>
bool List::Stack<T>::is_full() const {
    return _items == _size;
}

template <typename T>
bool List::Stack<T>::is_empty() const {
    return _items == 0;
}

template <typename T>
List::Stack<T> & List::Stack<T>::operator=(Stack<T> &&st) noexcept {
    if(&st == this) {
        return *this;
    }

    _items = st._items;
    _size = st._size;
    _front = std::move(st._front);
    st._front = nullptr;
    _rear = std::move(st._rear);
    st._rear = nullptr;

    return *this;
}



template<typename T>
Array::Stack<T>::Stack(std::size_t n) {
    _size = n;
    _stack_array = std::unique_ptr<T>(new T[_size]);
    _top = 0;
}

template<typename T>
Array::Stack<T>::Stack(const Array::Stack<T> &st) {
    _size = st._size;
    _stack_array = std::unique_ptr<T>(new T[_size]);
    _top = st._top;

    for (std::size_t i = 0; i < _size; i++) {
        _stack_array.get()[i] = st._stack_array.get()[i];
    }
}

template<typename T>
Array::Stack<T>::Stack(Stack &&st) noexcept {
    _size = st._size;
    _stack_array = std::move(st._stack_array);
    st._stack_array = nullptr;
    _top = st._top;
}

template<typename T>
bool Array::Stack<T>::push(const T &element) {
    if (_top < _size) {
        _stack_array.get()[_top++] = element;
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool Array::Stack<T>::pop(T &element) {
    if (_top > 0) {
        element = _stack_array.get()[--_top];
        return true;
    } else {
        return false;
    }
}

template <typename T>
std::size_t Array::Stack<T>::number_of_elements() const {
    return _top;
}

template<typename T>
bool Array::Stack<T>::is_full() const {
    return _top == _size;
}

template<typename T>
bool Array::Stack<T>::is_empty() const {
    return _top == 0;
}

template<typename T>
Array::Stack<T> &Array::Stack<T>::operator=(const Stack<T> &st) {
    if (this == &st) {
        return *this;
    }

    _size = st._size;
    _stack_array = std::unique_ptr<T>(new T[_size]);
    _top = st._top;

    for (std::size_t i = 0; i < _size; i++) {
        _stack_array.get()[i] = st._stack_array.get()[i];
    }

    return *this;
}


template<typename T>
Array::Stack<T> &Array::Stack<T>::operator=(Stack<T> &&st) noexcept {
    if (this == &st) {
        return *this;
    }

    _size = st._size;
    _stack_array = std::move(st._stack_array);
    st._stack_array = nullptr;
    _top = st._top;

    return *this;
}


#endif //LAB4_STACK_TCC
