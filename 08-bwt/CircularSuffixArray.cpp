#include "CircularSuffixArray.hpp"

CircularSuffixArray::CircularSuffixArray(const std::string &input)
    : n(input.size()), input_str(input) {
    p.resize(ALPHABET), cnt.resize(ALPHABET), c.resize(ALPHABET);
    for (size_t i = 0; i < n; ++i) {
        cnt[input[i]]++;
    }
    for (size_t i = 1; i < ALPHABET; ++i) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = static_cast<int>(n - 1); i >= 0; --i) {
        p[--cnt[input[i]]] = i;
    }
    c[p[0]] = 0;
    for (size_t i = 1; i < n; ++i) {
        if (input[p[i]] == input[p[i - 1]]) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }
    std::vector<int> pn(ALPHABET), cn(ALPHABET);
    for (size_t h = 0; (1 << h) < n; ++h) {
        for (size_t i = 0; i < n; ++i) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0) {
                pn[i] += n;
            }
        }
        for (size_t i = 0; i < ALPHABET; ++i) {
            cnt[i] = 0;
        }
        for (size_t i = 0; i < n; ++i) {
            ++cnt[c[pn[i]]];
        }
        for (size_t i = 1; i < ALPHABET; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = static_cast<int>(n - 1); i >= 0; --i) {
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        for (size_t i = 1; i < n; ++i) {
            cn[p[i]] = cn[p[i - 1]];
            if ((c[p[i]] != c[p[i - 1]]) || (c[(p[i] + (1 << h)) % n] != c[(p[i - 1] + (1 << h)) % n])) {
                cn[p[i]] = cn[p[i - 1]] + 1;
            }
        }
        for (size_t i = 0; i < n; i++) {
            c[i] = cn[i];
        }
    }
}

size_t CircularSuffixArray::size() const {
    return input_str.size();
}

size_t CircularSuffixArray::operator[](size_t n) const {
    return static_cast<size_t>(p[n]);
}
