#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include "randomized_queue.hpp"

#define EXPECT(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
            return; \
        } \
    } while (false)

size_t flag2 = 0;

void test2() {
    randomized_queue<int> q;
    for (int i = 0; i < 3; ++i) {
        q.enqueue(i + 1);
    }
    randomized_queue<int>::iterator it = q.begin();
    randomized_queue<int>::iterator it1 = it;
    ++it;
    randomized_queue<int>::iterator it2 = it;
    ++it;

    EXPECT(std::max((*it), std::max((*it1), (*it2))), 3, "Wrong answer in 'randomized_queue<int>::iterator'.");
    EXPECT(std::min((*it), std::min((*it1), (*it2))), 1, "Wrong answer in 'randomized_queue<int>::iterator'.");
    EXPECT((*it) + (*it1) + (*it2), 6, "Wrong answer in 'randomized_queue<int>::iterator'.");

    for (int i = 3; i < 5; ++i) {
        q.enqueue(i + 1);
    }

    std::vector<int> v1(5), v2, ans = { 1, 2, 3, 4, 5 };
    auto first = q.begin();
    auto last = q.end();
    auto result = v1.begin();
    while (first!=last) {
        *result = *first;
        ++result;
        ++first;
    }
    std::sort(v1.begin(), v1.end());
    EXPECT(v1, ans, "Wrong answer in 'randomized_queue<int>::iterator'.");
    int v = q.sample();
    assert(v >= 1 && v <= 5);

    while (!q.empty()) {
        v2.push_back(q.dequeue());
    }
    std::sort(v2.begin(), v2.end());
    EXPECT(v1, ans, "Wrong answer in method 'dequeue'.");

    flag2++;
}

int main1() {
    test2();

    if (flag2 == 1) {
        std::cout << "All tests passed successfully.";
    }

    return 0;
}
