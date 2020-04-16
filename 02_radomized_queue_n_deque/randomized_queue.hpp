#include <utility>

#ifndef HW2_RANDOMIZED_QUEUE_HPP
#define HW2_RANDOMIZED_QUEUE_HPP

#include <list>
#include <random>
#include <algorithm>
#include <iterator>

template<typename T>
class randomized_queue {
 public:
    randomized_queue()
        : head(0), tail(0), n(10) {
        m_data.resize(n);
    };

    bool empty() {
        return head == tail;
    }

    size_t size() {
        if (head > tail) {
            return (size_t) m_data.size() - head + tail;
        }
        return tail - head;
    }

    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
     private:
        std::vector<T> m_data;
        std::vector<size_t> perm;
        size_t current_pos, head, tail, n;
     public:
        iterator() = default;
        iterator(std::vector<T> &_m_data, size_t &_head, size_t &_tail, size_t &_n)
            : m_data(_m_data), head(_head), tail(_tail), n(_n) {
            current_pos = 0;
            if (head < tail) {
                for (size_t i = head; i < tail; ++i) {
                    perm.push_back(i);
                }
            } else {
                for (size_t i = head; i < n; ++i) {
                    perm.push_back(i);
                }
                for (size_t i = 0; i < tail; ++i) {
                    perm.push_back(i);
                }
            }
            std::random_device rd;
            std::mt19937_64 g(rd());
            std::shuffle(perm.begin(), perm.end(), g);
            perm.push_back(n);
        }

        T &operator*() {
            return m_data[perm[current_pos]];
        }

        iterator &operator++() {
            current_pos++;
            return *this;
        }

        iterator &operator--() {
            current_pos--;
            return *this;
        }

        iterator &operator++(int) {
            iterator tmp = *this;
            current_pos++;
            return tmp;
        }

        iterator &operator--(int) {
            iterator tmp = *this;
            current_pos--;
            return tmp;
        }

        iterator &operator+=(int n) {
            current_pos += n;
            return *this;
        }

        iterator &operator-=(int n) {
            current_pos -= n;
            return *this;
        }

        iterator operator+(int n) {
            current_pos += n;
            return *this;
        }

        iterator operator-(int n) {
            current_pos -= n;
            return *this;
        }

        bool operator==(const iterator &other) const {
            return perm[current_pos] == other.perm[other.current_pos] && m_data == other.m_data;
        }

        bool operator!=(const iterator &other) const {
            return perm[current_pos] != other.perm[other.current_pos] && m_data == other.m_data;
        }

        auto begin() {
            return *this;
        }

        auto end() {
            current_pos = (size_t)perm.size() - 1;
            return *this;
        }

        size_t get_pos() {
            return perm[0];
        }
    };

    auto begin() {
        iter = iterator(m_data, head, tail, n);
        return iter.begin();
    }

    auto end() {
        return iter.end();
    }

    void expand() {
        std::vector<T> a = m_data;
        m_data.clear();
        m_data.resize(n * 2);
        size_t p = 0;

        if (head > tail) {
            for (size_t i = head; i < n; ++i) {
                m_data[p++] = a[i];
            }
            for (size_t i = 0; i < tail; ++i) {
                m_data[p++] = a[i];
            }
        } else {
            for (size_t i = head; i < tail; ++i) {
                m_data[p++] = a[i];
            }
        }

        head = 0;
        tail = p;
        n *= 2;
        a.clear();
    }

    void enqueue(T value) {
        if (size() + 1 == n) {
            expand();
        }
        m_data[tail] = value;
        tail = (tail + 1) % n;
    }

    T sample() {
        iterator it(m_data, head, tail, n);
        return *it.begin();
    }

    T dequeue() {
        iter = iterator(m_data, head, tail, n);
        T value = *iter.begin();
        size_t pos = iter.get_pos(), p = 0;
        std::vector<T> new_data(n);
        if (head > tail) {
            for (size_t i = head; i < n; ++i) {
                if (i != pos) {
                    new_data[p++] = m_data[i];
                }
            }
            for (size_t i = 0; i < tail; ++i) {
                if (i != pos) {
                    new_data[p++] = m_data[i];
                }
            }
        } else {
            for (size_t i = head; i < tail; ++i) {
                if (i != pos) {
                    new_data[p++] = m_data[i];
                }
            }
        }
        head = 0;
        tail = p;
        m_data = new_data;
        new_data.clear();
        return value;
    }
 private:
    randomized_queue<T>::iterator iter;
    std::vector<T> m_data;
    size_t head, tail, n;
};

#endif
