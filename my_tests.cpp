#include <iostream>
#include <cassert>
#include <cmath>
#include <memory>
#include "Point.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Array.h"

using namespace std;

// Макросы для тестирования
#define TEST_CASE(name) cout << "\n" << name << ":\n"
#define CHECK(condition) \
    if (!(condition)) { \
        cout << "  ❌ FAIL: " << #condition << " (line " << __LINE__ << ")\n"; \
        return false; \
    } else { \
        cout << "  ✅ " << #condition << "\n"; \
    }

#define RUN_TEST(test_func) \
    cout << "\n=== " << #test_func << " ===" << endl; \
    if (test_func()) { \
        cout << "✅ PASSED\n"; \
        passed_tests++; \
    } else { \
        cout << "❌ FAILED\n"; \
        failed_tests++; \
    } \
    total_tests++;

int passed_tests = 0;
int failed_tests = 0;
int total_tests = 0;

// ========== ТЕСТЫ ==========

bool test_point() {
    TEST_CASE("Point конструкторы");
    Point<int> p1;
    CHECK(p1.getX() == 0);
    CHECK(p1.getY() == 0);
    
    Point<double> p2(3.5, 4.2);
    CHECK(fabs(p2.getX() - 3.5) < 1e-6);
    CHECK(fabs(p2.getY() - 4.2) < 1e-6);
    
    TEST_CASE("Point distance");
    Point<int> p3(0, 0);
    Point<int> p4(3, 4);
    CHECK(fabs(p3.distanceTo(p4) - 5.0) < 1e-6);
    
    return true;
}

bool test_triangle() {
    TEST_CASE("Triangle создание");
    Triangle<int> t(0, 0, 5);
    CHECK(t.getVertices().size() == 5);
    
    TEST_CASE("Triangle площадь");
    double area = t.area();
    CHECK(area > 0);
    
    TEST_CASE("Triangle геометрический центр");
    auto center = t.geometricCenter();
    CHECK(fabs(center.getX()) < 0.1);
    CHECK(fabs(center.getY()) < 0.1);
    
    TEST_CASE("Triangle копирование");
    Triangle<int> t2 = t;
    CHECK(t == t2);
    
    return true;
}

bool test_pentagon() {
    TEST_CASE("Pentagon создание");
    Pentagon<int> p(0, 0, 5);
    CHECK(p.getVertices().size() == 6);
    
    TEST_CASE("Pentagon площадь");
    CHECK(p.area() > 0);
    
    return true;
}

bool test_hexagon() {
    TEST_CASE("Hexagon создание");
    Hexagon<int> h(0, 0, 5);
    CHECK(h.getVertices().size() == 8);
    
    TEST_CASE("Hexagon площадь");
    CHECK(h.area() > 0);
    
    return true;
}

bool test_array() {
    TEST_CASE("Array базовые операции");
    Array<int> arr;
    CHECK(arr.getSize() == 0);
    
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    CHECK(arr.getSize() == 3);
    CHECK(arr[0] == 1);
    CHECK(arr[1] == 2);
    CHECK(arr[2] == 3);
    
    TEST_CASE("Array удаление");
    arr.remove(1);
    CHECK(arr.getSize() == 2);
    CHECK(arr[0] == 1);
    CHECK(arr[1] == 3);
    
    TEST_CASE("Array границы");
    try {
        int x = arr[10];
        CHECK(false); // Не должно дойти сюда
    } catch (const std::out_of_range&) {
        CHECK(true); // Должно бросить исключение
    }
    
    return true;
}

bool test_figure_operations() {
    TEST_CASE("Figure массив");
    Array<shared_ptr<Figure<int>>> figures;
    figures.push_back(make_shared<Triangle<int>>(0, 0, 5));
    figures.push_back(make_shared<Pentagon<int>>(0, 0, 4));
    figures.push_back(make_shared<Hexagon<int>>(0, 0, 3));
    
    CHECK(figures.getSize() == 3);
    
    TEST_CASE("Figure преобразование к double");
    for (size_t i = 0; i < figures.getSize(); ++i) {
        double area = static_cast<double>(*figures[i]);
        CHECK(area > 0);
    }
    
    TEST_CASE("Figure клонирование");
    auto original = figures[0];
    auto cloned = original->clone();
    CHECK(*original == *cloned);
    
    TEST_CASE("Figure общая площадь");
    double total = 0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        total += figures[i]->area();
    }
    CHECK(total > 0);
    
    return true;
}

bool test_different_types() {
    TEST_CASE("Разные типы данных");
    
    Triangle<int> t_int(0, 0, 5);
    CHECK(t_int.area() > 0);
    
    Triangle<double> t_double(0.0, 0.0, 5.5);
    CHECK(t_double.area() > 0);
    
    Triangle<float> t_float(0.0f, 0.0f, 5.5f);
    CHECK(t_float.area() > 0);
    
    return true;
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========

int main() {
    cout << "==========================================" << endl;
    cout << "Unit-тесты для лабораторной работы 4" << endl;
    cout << "==========================================" << endl;
    
    RUN_TEST(test_point);
    RUN_TEST(test_triangle);
    RUN_TEST(test_pentagon);
    RUN_TEST(test_hexagon);
    RUN_TEST(test_array);
    RUN_TEST(test_figure_operations);
    RUN_TEST(test_different_types);
    
    cout << "\n==========================================" << endl;
    cout << "РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ:" << endl;
    cout << "Всего тестов: " << total_tests << endl;
    cout << "Пройдено: " << passed_tests << endl;
    cout << "Провалено: " << failed_tests << endl;
    
    if (failed_tests == 0) {
        cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!" << endl;
    } else {
        cout << "❌ ЕСТЬ ПРОВАЛЕННЫЕ ТЕСТЫ" << endl;
    }
    cout << "==========================================" << endl;
    
    return failed_tests == 0 ? 0 : 1;
}
