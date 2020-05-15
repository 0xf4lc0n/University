#ifndef LAB6_LIST_H
#define LAB6_LIST_H

#include <iostream>
#include <memory>
#include <vector>
#include <set>

/**
 * Structure represents graph's edge
 */
struct Edge {
    int start_node;
    int end_node;
};

/**
 * Structure represents element in list
 */
struct Element {
    int node;
    std::unique_ptr<Element> next;

    explicit Element(int c_node) : node(c_node), next(nullptr) {}
};

/**
 * List implemented by structure
 */
namespace struct_example {
    struct List {
    private:
        std::unique_ptr<Element> _top;
        unsigned int _elements;
    public:
        List() : _top(nullptr), _elements(0) {}
        ~List() = default;
        List(const List &) = delete;
        List(List &&) = delete;
        List &operator=(const List &) = delete;
        List &operator=(List &&) = delete;
        void push_back(int e);
        friend std::ostream &operator<<(std::ostream &os, const List &L);
        [[nodiscard]] unsigned int number_of_elements() const noexcept;
    };
}

/**
 * List implemented by structure
 */
namespace class_example {
    class List{
        private:
            std::unique_ptr<Element> _top;
            unsigned int _elements;
        public:
            List() : _top(nullptr), _elements(0) {}
            ~List() = default;
            List(const List &) = delete;
            List(List &&) = delete;
            List &operator=(const List &) = delete;
            List &operator=(List &&) = delete;
            void push_back(int e);
            friend std::ostream &operator<<(std::ostream &os, const List &L);
            [[nodiscard]] unsigned int number_of_elements() const noexcept ;
    };
}

#endif //LAB6_LIST_H
