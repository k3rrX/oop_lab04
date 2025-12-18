#include <iostream>
#include <cassert>
#include "Point.h"
#include "Triangle.h"

int main() {
    std::cout << "Простой тест Point..." << std::endl;
    Point<int> p(10, 20);
    assert(p.getX() == 10);
    assert(p.getY() == 20);
    std::cout << "Point: OK" << std::endl;
    
    std::cout << "Простой тест Triangle..." << std::endl;
    Triangle<int> t(0, 0, 5);
    assert(t.getVertices().size() == 5);
    std::cout << "Triangle: OK" << std::endl;
    
    std::cout << "\n✅ Все простые тесты пройдены!" << std::endl;
    return 0;
}
