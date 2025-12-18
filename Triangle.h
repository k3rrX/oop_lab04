#pragma once
#include "Polygon.h"

template<typename T>
class Triangle : public Polygon<T> {
public:
    Triangle() : Polygon<T>(5) {}
    
    Triangle(T x, T y, T radius) : Polygon<T>(5) {
        createRegularPolygon(x, y, radius, 5);
    }

    Triangle(const Triangle& other) : Polygon<T>(5) {
        for (const auto& vertex : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
        }
    }

    Triangle& operator=(const Triangle& other) {
        if (this != &other) {
            this->vertices.clear();
            for (const auto& vertex : other.vertices) {
                this->vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
            }
        }
        return *this;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Triangle<T>>(*this);
    }

private:
    void createRegularPolygon(T centerX, T centerY, T radius, int sides) {
        const double pi = 3.141592653589793;
        for (int i = 0; i < sides; ++i) {
            double angle = 2 * pi * i / sides - pi / 2;
            T x = centerX + radius * std::cos(angle);
            T y = centerY + radius * std::sin(angle);
            this->vertices.push_back(std::make_unique<Point<T>>(x, y));
        }
    }
};
