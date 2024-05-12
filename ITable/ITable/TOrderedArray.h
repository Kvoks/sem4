#ifndef TOrderedArray_H
#define TOrderedArray_H

#include <functional>
#include <iostream>

#define DEFAULT_CAPACITY_SIZE 25
#define DEFAULT_CAPACITY_ADD 25
#define DEFAULT_MAXSIZE 0

template <typename T> class OrderedArray {
private:
    T* data;
    int size;
    int capacity;
    int maxSize;

public:
    OrderedArray(int initialCapacity = DEFAULT_CAPACITY_SIZE,
        int maxSize = DEFAULT_MAXSIZE)
        : size(0), capacity(initialCapacity), maxSize(maxSize) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Initial capacity must be positive");
        }
        if (maxSize < 0) {
            throw std::invalid_argument("Maximum size must be non-negative");
        }
        data = new T[capacity];
    }

    ~OrderedArray() { delete[] data; }

    void add(T element) {
        if (size == capacity) {
            if (maxSize != 0 && capacity + DEFAULT_CAPACITY_ADD > maxSize) {
                throw std::overflow_error("Maximum size exceeded");
            }
            capacity += DEFAULT_CAPACITY_ADD;
            T* newData = new T[capacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }

        int pos = 0;
        while (pos < size && data[pos] < element) {
            pos++;
        }

        for (int i = size; i > pos; i--) {
            data[i] = data[i - 1];
        }

        data[pos] = element;
        size++;

        if (size > maxSize && maxSize != 0) {
            throw std::overflow_error("Maximum size exceeded");
        }
    }

    T get(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    int getSize() { return size; }

    int getCapacity() { return capacity; }

    int find(std::function<bool(T)> predicate) {
        for (int i = 0; i < size; i++) {
            if (predicate(data[i])) {
                return i;
            }
        }
        return -1;
    }

    class iterator {
    private:
        T* ptr;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(T* p = nullptr) : ptr(p) {}

        reference operator*() const { return *ptr; }

        pointer operator->() { return ptr; }

        iterator& operator++() {
            ++ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++ptr;
            return tmp;
        }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }

        bool operator!=(const iterator& other) const { return !(*this == other); }
    };

    iterator begin() { return iterator(data); }

    iterator end() { return iterator(data + size); }
};
#endif