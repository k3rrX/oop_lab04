#pragma once
#include "Point.h"
#include <memory>
#include <vector>

template<typename T>
class Figure {
protected:
    std::vector<std::unique_ptr<Point<T>>> vertices;

public:
    virtual ~Figure() = default;

    virtual Point<T> geometricCenter() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual std::shared_ptr<Figure<T>> clone() const = 0;

    const std::vector<std::unique_ptr<Point<T>>>& getVertices() const {
        return vertices;
    }

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }

    virtual bool operator==(const Figure<T>& other) const {
        if (vertices.size() != other.vertices.size()) return false;
        for (size_t i = 0; i < vertices.size(); ++i) {
            if (!(*vertices[i] == *other.vertices[i])) {
                return false;
            }
        }
        return true;
    }

    operator double() const {
        return area();
    }
};
