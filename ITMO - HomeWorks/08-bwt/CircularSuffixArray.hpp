#ifndef HW08_CIRCULARSUFFIXARRAY_HPP
#define HW08_CIRCULARSUFFIXARRAY_HPP

#include <string>
#include <vector>

const size_t ALPHABET = 256;

class CircularSuffixArray
{
 private:
    size_t n;
    std::string input_str;
    std::vector<int> p, c, cnt;
 public:
    explicit CircularSuffixArray(const std::string& input);

    size_t size() const;

    size_t operator[](size_t n) const;
};

#endif
