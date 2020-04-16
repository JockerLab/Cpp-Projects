#include <iostream>
#include <vector>
#include "binary_search_deluxe.hpp"

size_t binary_search_deluxe::first_index_of(std::vector<term> a, term key, const std::function<bool(const term&, const term&)> &comparator) {
    auto n = a.size();
    size_t l = 0, r = n;

    while (l + 1 < r) {
        size_t m = (l + r) / 2;
        if (comparator(a[m], key)) {
            l = m;
        } else {
            r = m;
        }
    }
    if (!comparator(a[l], key) && n > 0) {
        r--;
    }
    return r;
}

size_t binary_search_deluxe::last_index_of(std::vector<term> a, term key, const std::function<bool(const term&, const term&)> &comparator) {
    auto n = a.size();
    size_t l = 0, r = n;

    while (l + 1 < r) {
        size_t m = (l + r) / 2;
        if (comparator(key, a[m])) {
            r = m;
        } else {
            l = m;
        }
    }

    return l;
}