#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include "randomized_queue.hpp"
#include "randomized_deque.hpp"

bool correct_string(std::string str) {
    for (char i : str) {
        if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')) {
            continue;
        }
        return false;
    }
    return true;
}

std::vector<std::string> solve(size_t cnt, std::vector<std::string> lines) {
    randomized_queue<std::string> q;
    randomized_queue<std::string>::iterator it;

    for (const std::string &line : lines) {
        assert(correct_string(line));
        q.enqueue(line);
    }

    it = q.begin();

    std::vector<std::string> result;

    for (size_t i = 0; i < cnt; ++i) {
        result.push_back((*it));
    }

    return result;
}
