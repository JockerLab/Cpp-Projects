#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <map>
#include "subset.hpp"

#define EXPECT(actual, expected, msg) \
    do { \
        if ((actual) != (expected)) { \
            std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
            return; \
        } \
    } while (false)

size_t flag3 = 0;

void check(std::vector<std::string> &in, std::vector<std::string> &ans) {
    for (const std::string &i : ans) {
        bool visited = false;
        for (const std::string &j : in) {
            if (i == j) {
                visited = true;
                break;
            }
        }
        if (!visited) {
            flag3--;
            std::cerr << __FILE__ << ":" << __LINE__ << " Found nonexistent string." << std::endl;
            return;
        }
    }
}

void test() {
    std::vector<std::string> in1 = { "A", "B", "C", "D", "E", "F" }
        , in2 = { "Aa", "aaAa", "aaaAaAa", "A" }
        , in3 = { "ABC", "AAldkS", "PAadSDDAS", "adASDAdaSD", "ads", "qdASD", "ASDADAS" };
    std::vector<std::string> ans1 = solve(3, in1), ans2 = solve(3, in2), ans3 = solve(4, in3);

    check(in1, ans1);
    check(in2, ans2);
    check(in3, ans3);

    flag3++;
}

int main() {
    test();

    if (flag3 == 1) {
        std::cout << "All tests passed successfully.";
    }

    return 0;
}
