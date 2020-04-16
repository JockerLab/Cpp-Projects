#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <functional>
#include <cassert>
#include <vector>
#include "term.hpp"
#include "binary_search_deluxe.hpp"
#include "autocomplete.hpp"

int flag = 0;

#define EXPECT(actual, expected, msg) \
    { \
        if ((actual) != (expected)) { \
            std::cerr << __FILE__ << ":" << __LINE__ << " " << msg << std::endl; \
            return; \
        } \
    }

void test_term() {
    size_t w1 = 10, w2 = 20, w3 = 30, w4 = 40;
    std::string s1 = "abacaba", s2 = "abcbac", s3 = "cacke", s4 = "abacaba";
    term t1(s1, w1);
    term t2(s2, w2);
    term t3(s3, w3);
    term t4(s4, w4);

    // to_string
    EXPECT(t1.to_string(), "10 abacaba", "Wrong answer on test method 'to_string'.")
    EXPECT(t2.to_string(), "20 abcbac", "Wrong answer on test method 'to_string'.")

    // by_reverse_weight_order
    EXPECT(t1.by_reverse_weight_order()(t1, t2), false, "Wrong answer on test method 'by_reverse_weight_order'.");
    EXPECT(t1.by_reverse_weight_order()(t2, t1), true, "Wrong answer on test method 'by_reverse_weight_order'.");
    EXPECT(t1.by_reverse_weight_order()(t1, t4), true, "Wrong answer on test method 'by_reverse_weight_order'.");
    EXPECT(t1.by_reverse_weight_order()(t4, t1), false, "Wrong answer on test method 'by_reverse_weight_order'.");

    // by_prefix_order
    EXPECT(t1.by_prefix_order(4)(t1, t3), true, "Wrong answer on test method 'by_prefix_order'.");
    EXPECT(t1.by_prefix_order(4)(t3, t1), false, "Wrong answer on test method 'by_prefix_order'.");
    EXPECT(t1.by_prefix_order(2)(t1, t2), false, "Wrong answer on test method 'by_prefix_order'.");
    EXPECT(t1.by_prefix_order(2)(t2, t1), false, "Wrong answer on test method 'by_prefix_order'.");

    flag++;
}

bool cmp2(const term &t1, const term &t2) {
    return t1 < t2;
}

class cmp3 {
 public:
    cmp3() = default;
    bool operator()(const term &t1, const term &t2) {
        return t1 < t2;
    }
};

void test_binary_search() {
    size_t w1 = 10, w2 = 20, w3 = 30, w4 = 20;
    std::string s1 = "abacaba", s2 = "abcbac", s3 = "cacke", s4 = "abcbac";
    term t1(s1, w1);
    term t2(s2, w2);
    term t3(s3, w3);
    term t4(s4, w4);

    std::vector<term> a = {t1, t4, t2, t3};

    auto cmp1 = [](const term &t1, const term &t2) { return t1 < t2; };

    // last_index_of
    EXPECT(binary_search_deluxe::last_index_of(a, t2, cmp1), 2, "Wrong answer on test method 'last_index_of'.");
    EXPECT(binary_search_deluxe::last_index_of(a, t2, cmp2), 2, "Wrong answer on test method 'last_index_of'.");
    EXPECT(binary_search_deluxe::last_index_of(a, t2, cmp3()), 2, "Wrong answer on test method 'last_index_of'.");

    // first_index_of
    EXPECT(binary_search_deluxe::first_index_of(a, t2, cmp1), 1, "Wrong answer on test method 'first_index_of'.");
    EXPECT(binary_search_deluxe::first_index_of(a, t2, cmp2), 1, "Wrong answer on test method 'first_index_of'.");
    EXPECT(binary_search_deluxe::first_index_of(a, t2, cmp3()), 1, "Wrong answer on test method 'first_index_of'.");

    flag++;
}

void test_autocomplete() {
    size_t w1 = 10, w2 = 20, w3 = 30, w4 = 20, w5 = 40;
    std::string s1 = "abacaba", s2 = "abcbac", s3 = "cacke", s4 = "abcbac", s5 = "abcaba", pref1 = "ab", pref2 = "abc";
    term t1(s1, w1);
    term t2(s2, w2);
    term t3(s3, w3);
    term t4(s4, w4);
    term t5(s5, w5);

    std::vector<term> a = {t1, t4, t2, t3}, a2 = {t5, t4, t2}, ans1 = {t1, t2, t4}, ans2 = {t2, t4}, ans3 = {t5, t4, t2};

    autocomplete a_complete(a);
    autocomplete a_complete2(a2);

    // all_matches
    EXPECT(a_complete.all_matches(pref1), ans1, "Wrong answer on test method 'all_matches'.");
    EXPECT(a_complete.all_matches(pref2), ans2, "Wrong answer on test method 'all_matches'.");
    EXPECT(a_complete2.all_matches(pref2), ans3, "Wrong answer on test method 'all_matches'.");

    // number_of_matches
    EXPECT(a_complete.number_of_matches(pref1), 3, "Wrong answer on test method 'number_of_matches'.");
    EXPECT(a_complete.number_of_matches(pref2), 2, "Wrong answer on test method 'number_of_matches'.");
    EXPECT(a_complete2.number_of_matches(pref2), 3, "Wrong answer on test method 'number_of_matches'.");

    flag++;
}

int main() {
    test_term();
    test_binary_search();
    test_autocomplete();

    if (flag == 3) {
        std::cout << "All tests passed successfully.";
    }

    return 0;
}