#pragma once
#include "Polygon.h"

template<typename T>
class Hexagon : public Polygon<T> {
public:
    Hexagon() : Polygon<T>(8) {}
    
    Hexagon(T x, T y, T radius) : Polygon<T>(8) {
        createRegularPolygon(x, y, radius, 8);
    }

    Hexagon(const Hexagon& other) : Polygon<T>(8) {
        for (const auto& vertex : other.vertices) {
            this->vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
        }
    }

    Hexagon& operator=(const Hexagon& other) {
        if (this != &other) {
            this->vertices.clear();
            for (const auto& vertex : other.vertices) {
                this->vertices.push_back(std::make_unique<Point<T>>(vertex->getX(), vertex->getY()));
            }
        }
        return *this;
    }

    std::shared_ptr<Figure<T>> clone() const override {
        return std::make_shared<Hexagon<T>>(*this);
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
