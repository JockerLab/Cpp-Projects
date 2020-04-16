#ifndef HW08_BWT_HPP
#define HW08_BWT_HPP

#include <iostream>
#include "MoveToFront.hpp"
#include "CircularSuffixArray.hpp"

class BWT
{
 private:
    size_t pos;
 public:
    BWT() = default;

    void transform(std::istream& input, std::ostream& output);

    void inverseTransform(std::istream& input, std::ostream& output);
};

#endif
