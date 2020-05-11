#ifndef LAB9_SUBJECT_TCC
#define LAB9_SUBJECT_TCC

#include <string>

/**
 * Class represents single subject
 * @tparam T - price's and weight's type
 */
template<typename T>
class Subject {
private:
    std::string name;
    T weight;
    T price;
public:
    explicit Subject(std::string n = "", T w = 0, T p = 0) : name(std::move(n)), weight(w), price(p) {}

    Subject(const Subject &) = default;

    Subject(Subject &&) noexcept = default;

    const T & get_weight() const { return weight; }

    const T & get_price() const { return price; }

    const T & get_name() const { return name; }

    ~Subject() = default;
};

#endif //LAB9_SUBJECT_TCC
