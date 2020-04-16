#ifndef PRACTICE_BINARY_SEARCH_DELUXE_HPP
#define PRACTICE_BINARY_SEARCH_DELUXE_HPP

#include <vector>
#include "term.hpp"

class binary_search_deluxe {
 public:
    static size_t first_index_of(std::vector<term> a, term key, const std::function<bool(const term&, const term&)> &comparator);
    static size_t last_index_of(std::vector<term> a, term key, const std::function<bool(const term&, const term&)> &comparator);
 private:
    binary_search_deluxe() {};
};

#endif
