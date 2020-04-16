#include <iostream>
#include <vector>
#include "randomized_deque.hpp"

#define EXPECT(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
            return; \
        } \
    } while (false)

size_t flag1 = 0;

void test1() {
    randomized_deque<int> d;

    for (int i = 0; i < 5; ++i) {
        d.push_front(i + 1);
    }
    for (int i = 1; i < 5; ++i) {
        d.push_back(i + 1);
    }

    auto b = d.begin();
    auto e = d.end();

    std::vector<int> v1, v2 = { 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::copy(b, e, std::back_inserter(v1));
    EXPECT(v1, v2, "Wrong answer in deque.");
    EXPECT(v1.front(), 5, "Wrong answer using 'front()' in deque.");
    EXPECT(v1.back(), 5, "Wrong answer using 'back()' in deque.");
    d.pop_back();
    d.pop_front();

    b = d.begin();
    e = d.end();
    v2 = { 4, 3, 2, 1, 2, 3, 4 };
    v1.clear();
    std::copy(b, e, std::back_inserter(v1));
    EXPECT(v1, v2, "Wrong answer in deque.");
    EXPECT(v1.front(), 4, "Wrong answer using 'front()' in deque.");
    EXPECT(v1.back(), 4, "Wrong answer using 'back()' in deque.");
    EXPECT(d.empty(), false, "Wrong answer in method 'empty'.");
    EXPECT(d.size(), 7, "Wrong answer in method 'size'.");
    EXPECT(d[0], 4, "Wrong answer in operator[].");
    EXPECT(d[3], 1, "Wrong answer in operator[].");

    flag1++;
}

int main2()
{
    test1();

    if (flag1 == 1) {
        std::cout << "All tests passed successfully.";
    }

    return 0;
}
