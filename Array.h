#pragma once
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
class Array {
private:
    std::vector<T> data;

public:
    Array() = default;
    
    Array(size_t initialCapacity) {
        data.reserve(initialCapacity);
    }
    
    Array(std::initializer_list<T> init) : data(init) {}

    void push_back(const T& value) {
        data.push_back(value);
    }

    void push_back(T&& value) {
        data.push_back(std::move(value));
    }

    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
    }

    T& operator[](size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const { return data.size(); }
    size_t getCapacity() const { return data.capacity(); }

    auto begin() { return data.begin(); }
    auto begin() const { return data.begin(); }
    auto end() { return data.end(); }
    auto end() const { return data.end(); }

    // Для совместимости с требованиями лабораторной
    void addMoveElement(T&& element) {
        push_back(std::move(element));
    }
};