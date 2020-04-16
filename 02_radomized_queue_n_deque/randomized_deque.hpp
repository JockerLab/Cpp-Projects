#ifndef HW2_RANDOMIZED_DEQUE_HPP
#define HW2_RANDOMIZED_DEQUE_HPP

#include <list>
#include <cassert>

template<typename T>
class randomized_deque {
 private:
    std::list<T> m_data;
 public:
    randomized_deque() = default;

    bool empty() const {
        return m_data.empty();
    }

    size_t size() {
        return (size_t) m_data.size();
    }

    auto begin() {
        return m_data.begin();
    }

    auto end() {
        return m_data.end();
    }

    void push_back(T value) {
        m_data.push_back(value);
    }

    void push_front(T value) {
        m_data.push_front(value);
    }

    T front() {
        assert(!m_data.empty());
        return m_data.front();
    }

    T back() {
        assert(!m_data.empty());
        return m_data.back();
    }

    void pop_back() {
        assert(!m_data.empty());
        m_data.pop_back();
    }

    void pop_front() {
        assert(!m_data.empty());
        m_data.pop_front();
    }

    const T& operator[](size_t x) const {
        auto it = m_data.begin();

        for (size_t i = 0; i < x; i++) {
            it++;
        }

        return *it;
    }

    T& operator[](size_t x) {
        auto it = m_data.begin();

        for (size_t i = 0; i < x; i++) {
            it++;
        }

        return *it;
    }
};

#endif
