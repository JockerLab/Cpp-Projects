#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <sstream>
#include "MoveToFront.hpp"

void initialize(std::array<char, 256> &symb) {
    char c = 0;
    for (size_t i = 0; i < ALPHABET; ++i, ++c) {
        symb[i] = c;
    }
}

void MoveToFront::encode(std::istream &input, std::ostream &output) {
    initialize(symb);
    unsigned char c;

    while (input >> c) {
        size_t pos = 0;
        for (size_t j = 0; j < ALPHABET; ++j) {
            if (symb[j] == c) {
                pos = j;
                break;
            }
        }
        output << pos << '\n';
        for (size_t j = pos; j > 0; --j) {
            symb[j] = symb[j - 1];
        }
        symb[0] = c;
    }
}

void MoveToFront::decode(std::istream &input, std::ostream &output) {
    initialize(symb);
    std::string res;
    unsigned char c;

    while (input >> c) {
        auto num = static_cast<size_t>(c);
        output << symb[num] << '\n';
        res += symb[num];
        for (size_t j = num; j > 0; --j) {
            symb[j] = symb[j - 1];
        }
        symb[0] = c;
    }

    assert(str == res);
}
