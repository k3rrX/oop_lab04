#pragma once
#include <iostream>
#include <memory>
#include <cmath>
#include <type_traits>

template<typename T>
class Point {
private:
    T x, y;

public:
    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}

    T getX() const { return x; }
    T getY() const { return y; }
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }

    double distanceTo(const Point<T>& other) const {
        T dx = x - other.x;
        T dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Point<T> operator+(const Point<T>& other) const {
        return Point<T>(x + other.x, y + other.y);
    }

    Point<T> operator/(T scalar) const {
        return Point<T>(x / scalar, y / scalar);
    }

    bool operator==(const Point<T>& other) const {
        return std::abs(x - other.x) < 1e-6 && std::abs(y - other.y) < 1e-6;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};
