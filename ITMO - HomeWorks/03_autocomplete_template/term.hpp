#ifndef PRACTICE_TERM_HPP
#define PRACTICE_TERM_HPP

#include <cstdio>
#include <string>
#include <sstream>
#include <functional>
#include <cassert>

class term {
 private:
    std::string str;
    size_t weight;
 public:
    term();

    term(const std::string &new_str, size_t new_weight);

    term(const term &t);

    term(term &&t);

    friend bool operator<(const term &t1, const term &t2);

    friend bool operator>(const term &t1, const term &t2);

    term &operator=(const term &t);

    friend bool operator!=(const std::vector<term> &t1, const std::vector<term> &t2);

    std::string to_string();

    friend std::ostream &operator<<(std::ostream &out, const term &t);

    std::function<bool(const term &t1, const term &t2)> by_reverse_weight_order();

    std::function<bool(const term &t1, const term &t2)> by_prefix_order(size_t new_r);

    std::string get_str() const;
};

#endif
