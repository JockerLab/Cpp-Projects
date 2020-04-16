#include "BWT.hpp"

void BWT::transform(std::istream &input, std::ostream &output) {
    std::string str, res;
    std::getline(input, str);
    CircularSuffixArray suffixArray = CircularSuffixArray(str + '#');

    for (size_t i = 0; i < str.size() + 1; ++i) {
        if (suffixArray[i] == 0) {
            pos = i;
            res += '#';
        } else {
            res += str[suffixArray[i] - 1];
        }
    }

    output << pos << '\n' << res;
}

void BWT::inverseTransform(std::istream &input, std::ostream &output) {
    size_t start = 0;
    std::string str, res;
    std::getline(input, str);
    std::vector<size_t> count(ALPHABET, 0), a(ALPHABET), t(str.size());

    for (size_t i = 0; i < str.size(); ++i) {
        count[str[i]]++;
    }
    for (size_t i = 0; i < ALPHABET; ++i) {
        a[i] = start;
        start += count[i];
    }
    for (size_t i = 0; i < str.size(); ++i) {
        t[a[str[i]]++] = i;
    }
    size_t j = pos;
    for (size_t i = 0; i < str.size(); ++i, j = t[j]) {
        if (str[j] != '#') {
            res += str[j];
        }
    }

    output << res;
}
