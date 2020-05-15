#include "auxiliary.h"
#include "../input_sanitization/input_sanitization.tcc"

namespace struct_example {
    void List::push_back(int e) {
        auto tmp_ptr = std::make_unique<Element>(e);
        _elements++;
        if (_top == nullptr) {
            _top = std::move(tmp_ptr);
        } else {
            tmp_ptr->next = std::move(_top);
            _top = std::move(tmp_ptr);
        }
    }

    std::ostream &operator<<(std::ostream &os, const List &L) {
        Element *top_element = L._top.get();

        while (top_element) {
            os << top_element->node << " ";
            top_element = top_element->next.get();
        }

        return os;
    }

    [[nodiscard]] unsigned int List::number_of_elements() const noexcept {
        return _elements;
    }
}

namespace class_example {
    void List::push_back(int e) {
        auto tmp_ptr = std::make_unique<Element>(e);
        _elements++;
        if (_top == nullptr) {
            _top = std::move(tmp_ptr);
        } else {
            tmp_ptr->next = std::move(_top);
            _top = std::move(tmp_ptr);
        }
    }

    std::ostream &operator<<(std::ostream &os, const List &L) {
        Element *top_element = L._top.get();

        while (top_element) {
            os << top_element->node << " ";
            top_element = top_element->next.get();
        }

        return os;
    }

    [[nodiscard]] unsigned int List::number_of_elements() const noexcept {
        return _elements;
    }
}