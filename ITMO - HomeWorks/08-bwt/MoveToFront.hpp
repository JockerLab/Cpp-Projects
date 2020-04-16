#ifndef HW08_MOVETOFRONT_HPP
#define HW08_MOVETOFRONT_HPP

#include <array>
#include "CircularSuffixArray.hpp"

class MoveToFront {
 private:
    std::string str;
    std::array<char, 256> symb;
 public:
    MoveToFront() = default;

    void encode(std::istream &input, std::ostream &output);

    void decode(std::istream &input, std::ostream &output);
};

#endif
