#include "term.hpp"

term::term()
    : weight(0) {}

term::term(const std::string &new_str, size_t new_weight)
    : str(new_str), weight(new_weight) {}

term::term(const term &t) = default;

term::term(term &&) = default;

bool operator<(const term &t1, const term &t2) {
    if (t1.str == t2.str) {
        return t1.weight > t2.weight;
    }
    return t1.str < t2.str;
}

bool operator>(const term &t1, const term &t2) {
    if (t1.str == t2.str) {
        return t1.weight < t2.weight;
    }
    return t1.str > t2.str;
}

term &term::operator=(const term &t) {
    if (this != &t) {
        str = t.str;
        weight = t.weight;
    }

    return *this;
}

bool operator!=(const std::vector<term> &t1, const std::vector<term> &t2) {
    if (t1.size() != t2.size()) {
        return true;
    }
    for (size_t i = 0; i < t1.size(); ++i) {
        if (t1[i].str != t2[i].str || t1[i].weight != t2[i].weight) {
            return true;
        }
    }
    return false;
}

std::string term::to_string() {
    std::ostringstream oss;
    oss << weight << " " << str;
    return oss.str();
}

std::ostream &operator<<(std::ostream &out, const term &t) {
    out << t.weight << " " << t.str;
    return out;
}

bool functor_reverse(const term &t1, const term &t2) {
    return t1 > t2;
}

class functor_prefix {
 private:
    size_t r;
 public:
    functor_prefix(size_t new_r) : r(new_r) {}
    bool operator()(const term &t1, const term &t2) {
        for (size_t i = 0; i < r; ++i) {
            if (t1.get_str()[i] < t2.get_str()[i]) {
                return true;
            }
            if (t1.get_str()[i] > t2.get_str()[i]) {
                return false;
            }
        }
        return false;
    }
};

std::function<bool(const term &t1, const term &t2)> term::by_reverse_weight_order() {
    return functor_reverse;
}

std::function<bool(const term &t1, const term &t2)> term::by_prefix_order(size_t new_r) {
    auto pref = functor_prefix(new_r);
    return pref;
}

std::string term::get_str() const {
    return str;
}

