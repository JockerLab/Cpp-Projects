#ifndef PRACTICE_AUTOCOMPLETE_HPP
#define PRACTICE_AUTOCOMPLETE_HPP

#include <vector>
#include "term.hpp"
#include "binary_search_deluxe.hpp"

class autocomplete {
 private:
    std::vector<term> array;
 public:
    autocomplete(std::vector<term> a);

    std::vector<term> all_matches(const std::string &prefix);

    size_t number_of_matches(const std::string &prefix);
};

#endif
