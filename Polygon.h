#pragma once
#include "Figure.h"

template<typename T>
class Polygon : public Figure<T> {
protected:
    int sides;

public:
    Polygon() : sides(0) {}
    Polygon(int sides) : sides(sides) {}

    Point<T> geometricCenter() const override {
        if (this->vertices.empty()) return Point<T>(0, 0);
        
        T sumX = 0, sumY = 0;
        for (const auto& vertex : this->vertices) {
            sumX += vertex->getX();
            sumY += vertex->getY();
        }
        return Point<T>(sumX / this->vertices.size(), sumY / this->vertices.size());
    }

    double area() const override {
        if (this->vertices.size() < 3) return 0.0;
        
        double area = 0.0;
        for (size_t i = 0; i < this->vertices.size(); ++i) {
            const auto& p1 = *this->vertices[i];
            const auto& p2 = *this->vertices[(i + 1) % this->vertices.size()];
            area += p1.getX() * p2.getY() - p2.getX() * p1.getY();
        }
        return std::abs(area) / 2.0;
    }

    void print(std::ostream& os) const override {
        os << this->sides << "-угольник: ";
        for (const auto& vertex : this->vertices) {
            os << *vertex << " ";
        }
        os << "\nЦентр: " << geometricCenter();
        os << "\nПлощадь: " << area();
    }

    virtual ~Polygon() = default;
};
