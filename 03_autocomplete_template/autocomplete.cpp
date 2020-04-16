#include <utility>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "autocomplete.hpp"

autocomplete::autocomplete(std::vector<term> a) {
    std::sort(a.begin(), a.end());
    array = std::move(a);
}
std::vector<term> autocomplete::all_matches(const std::string &prefix) {
    std::vector<term> result;
    if (array.empty()) {
        return result;
    }
    size_t pos_l = binary_search_deluxe::first_index_of(array, term(prefix, 0), term().by_prefix_order(prefix.size()))
    , pos_r = binary_search_deluxe::last_index_of(array, term(prefix, 0), term().by_prefix_order(prefix.size()));
    for (size_t i = pos_l; i <= std::min(array.size() - 1, pos_r); ++i) {
        result.push_back(array[i]);
    }
    return result;
}
size_t autocomplete::number_of_matches(const std::string &prefix) {
    if (array.empty()) {
        return 0;
    }
    size_t pos_l = binary_search_deluxe::first_index_of(array, term(prefix, 0), term().by_prefix_order(prefix.size()))
    , pos_r = binary_search_deluxe::last_index_of(array, term(prefix, 0), term().by_prefix_order(prefix.size()));
    if (pos_l == array.size()) {
        return 0;
    }
    return pos_r - pos_l + 1;
}
