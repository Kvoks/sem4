#ifndef TVector_H
#define TVector_H

#include "IVector.h"
#include <iostream>
#define DEFAULT_CAPASOTY_SIZE 25
#define DEFAULT_CAPASOTY_ADD 25
#define DEFAULT_MAXSIZE 0

template <typename T> class TVector : public IVector<T> {
    T* data;
    size_t size;
    size_t capacity;
    size_t maxSize;

public:
    TVector() {
        data = new T[DEFAULT_CAPASOTY_SIZE];
        capacity = DEFAULT_CAPASOTY_SIZE;
        size = 0;
        maxSize = DEFAULT_MAXSIZE;
    }
    TVector(size_t capacity_, size_t maxSize = DEFAULT_MAXSIZE) {
        data = new T[capacity_];
        capacity = capacity_;
        size = 0;
    }
    TVector(const TVector& other) {
        data = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        maxSize = other.maxSize;
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    ~TVector() {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
        maxSize = 0;
    }
    TVector& operator=(const TVector& other) {
        if (this == &other) {
            return *this;
        }
        else {
            return &TVector(other);
        }
    }

    void remove(const T& data_) {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (data[i] == data_) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            return;
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }

    void clear() { size = 0; }

    size_t Size() { return size; }

    bool isEmpty() { return size == 0; }

    void push_back(const T& data_) {
        if (size == maxSize && maxSize != 0) {
            throw std::logic_error("Vector is full");
        }
        if (size == capacity) {
            T* tmp = new T[capacity + DEFAULT_CAPASOTY_ADD];
            for (int i = 0; i < size; i++) {
                tmp[i] = data[i];
            }
            delete[] data;
            data = tmp;
            capacity += DEFAULT_CAPASOTY_ADD;
        }
        data[size] = data_;
        size++;
    }

    void push_front(const T& data_) {
        if (size == maxSize && maxSize != 0) {
            throw std::logic_error("Vector is full");
        }
        if (size == capacity) {
            T* tmp = new T[capacity + DEFAULT_CAPASOTY_ADD];
            for (int i = 0; i < size; i++) {
                tmp[i + 1] = data[i];
            }
            delete[] data;
            data = tmp;
            capacity += DEFAULT_CAPASOTY_ADD;
        }
        else {
            for (int i = size; i > 0; i--) {
                data[i] = data[i - 1];
            }
        }
        data[0] = data_;
        size++;
    }
    void pop_back() {
        if (size == 0) {
            throw std::logic_error("Vector is empty");
        }
        size--;
    }


    void pop_front() {
        if (size == 0) {
            throw std::logic_error("Vector is empty");
        }
        for (int i = 0; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin() { return data; }

    const_iterator begin() const { return data; }

    iterator end() { return data + size; }

    const_iterator end() const { return data + size; }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    template <typename Predicate> iterator find_if(Predicate pred) {
        for (iterator it = begin(); it != end(); ++it) {
            if (pred(*it)) {
                return it;
            }
        }
        return end();
    }
};
#endif