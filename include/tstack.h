// Copyright 2021 NNTU-CS
#ifndef TSTACK_H_
#define TSTACK_H_

#include <cstddef>
#include <stdexcept>

template<typename T>
class TStack {
public:
    explicit TStack(size_t initialCapacity = 100)
        : capacity(initialCapacity), topIndex(0) {
        data = new T[capacity];
    }

    ~TStack() { delete[] data; }

    void push(const T& value) {
        if (topIndex >= capacity) {
            size_t newCapacity = capacity * 2;
            T* newData = new T[newCapacity];
            for (size_t i = 0; i < capacity; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
        data[topIndex++] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        --topIndex;
    }

    T get() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty!");
        }
        return data[topIndex - 1];
    }

    bool isEmpty() const { return topIndex == 0; }

    size_t size() const { return topIndex; }

    void clear() { topIndex = 0; }

private:
    T* data;
    size_t capacity;
    size_t topIndex;
};

#endif  // TSTACK_H_
