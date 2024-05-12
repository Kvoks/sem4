#ifndef TPair_H
#define TPair_H

#include <iostream>
template <typename T1, typename T2>
class TPair {
    T1 first;
    T2 second;

public:
    TPair(T1 first, T2 second) : first(first), second(second) {}
    T1 getFirst() { return first; }
    T2 getSecond() { return second; }
    void setFirst(T1 first) { this->first = first; }
    void setSecond(T2 second) { this->second = second; }
    void print() {
        std::cout << first << " " << second << std::endl;
    }
    TPair& operator=(const TPair& other) {
        TPair<T1, T2> tmp(other.first, other.second);
        return tmp;
    }
};
#endif