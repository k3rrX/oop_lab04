#include <iostream>
#include <memory>
#include <cmath>
#include <cassert>
#include <vector>
#include "Point.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Array.h"

using namespace std;

// Минимальная имитация Google Test
class TestRunner {
private:
    int passed;
    int failed;
    
public:
    TestRunner() : passed(0), failed(0) {}
    
    template<typename T>
    void EXPECT_EQ(const T& actual, const T& expected, const string& message) {
        if (actual == expected) {
            cout << "  ✅ " << message << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << " (expected " << expected << ", got " << actual << ")" << endl;
            failed++;
        }
    }
    
    template<typename T>
    void EXPECT_NE(const T& actual, const T& expected, const string& message) {
        if (actual != expected) {
            cout << "  ✅ " << message << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << " (values are equal)" << endl;
            failed++;
        }
    }
    
    template<typename T>
    void EXPECT_GT(const T& actual, const T& expected, const string& message) {
        if (actual > expected) {
            cout << "  ✅ " << message << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << " (" << actual << " <= " << expected << ")" << endl;
            failed++;
        }
    }
    
    // Для разных типов (например, double и float)
    void EXPECT_GT_DOUBLE(double actual, double expected, const string& message) {
        if (actual > expected) {
            cout << "  ✅ " << message << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << " (" << actual << " <= " << expected << ")" << endl;
            failed++;
        }
    }
    
    void EXPECT_NEAR(double actual, double expected, double epsilon, const string& message) {
        if (fabs(actual - expected) <= epsilon) {
            cout << "  ✅ " << message << " (" << actual << " ≈ " << expected << ")" << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << " (" << actual << " != " << expected << ", diff: " << fabs(actual - expected) << ")" << endl;
            failed++;
        }
    }
    
    void EXPECT_TRUE(bool condition, const string& message) {
        if (condition) {
            cout << "  ✅ " << message << endl;
            passed++;
        } else {
            cout << "  ❌ " << message << endl;
            failed++;
        }
    }
    
    void Report() {
        cout << "\n========================================" << endl;
        cout << "ТЕСТЫ ЗАВЕРШЕНЫ" << endl;
        cout << "Пройдено: " << passed << endl;
        cout << "Провалено: " << failed << endl;
        cout << "Всего: " << (passed + failed) << endl;
        
        if (failed == 0) {
            cout << "✅ ВСЕ ТЕСТЫ ПРОЙДЕНЫ!" << endl;
        } else {
            cout << "❌ ЕСТЬ ПРОВАЛЕННЫЕ ТЕСТЫ" << endl;
        }
        cout << "========================================" << endl;
    }
};

// Тестовые функции
void RunAllTests() {
    TestRunner runner;
    
    cout << "=== ТЕСТИРОВАНИЕ Point ===" << endl;
    {
        Point<int> p1;
        runner.EXPECT_EQ(p1.getX(), 0, "Point default constructor X");
        runner.EXPECT_EQ(p1.getY(), 0, "Point default constructor Y");
        
        Point<double> p2(3.5, 4.2);
        runner.EXPECT_EQ(p2.getX(), 3.5, "Point parameterized constructor X");
        runner.EXPECT_EQ(p2.getY(), 4.2, "Point parameterized constructor Y");
        
        Point<int> p3(0, 0);
        Point<int> p4(3, 4);
        runner.EXPECT_EQ(p3.distanceTo(p4), 5.0, "Point distance calculation");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ Triangle (5-угольник) ===" << endl;
    {
        Triangle<int> t(0, 0, 5);
        runner.EXPECT_EQ((int)t.getVertices().size(), 5, "Triangle has 5 vertices");
        runner.EXPECT_GT(t.area(), 0.0, "Triangle area is positive");
        
        auto center = t.geometricCenter();
        runner.EXPECT_NEAR(center.getX(), 0, 0.1, "Triangle center X");
        runner.EXPECT_NEAR(center.getY(), 0, 0.1, "Triangle center Y");
        
        Triangle<int> t2 = t;
        runner.EXPECT_TRUE(t == t2, "Triangle copy constructor");
        
        auto clone = t.clone();
        runner.EXPECT_TRUE(t == *clone, "Triangle clone method");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ Pentagon (6-угольник) ===" << endl;
    {
        Pentagon<int> p(0, 0, 5);
        runner.EXPECT_EQ((int)p.getVertices().size(), 6, "Pentagon has 6 vertices");
        runner.EXPECT_GT(p.area(), 0.0, "Pentagon area is positive");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ Hexagon (8-угольник) ===" << endl;
    {
        Hexagon<int> h(0, 0, 5);
        runner.EXPECT_EQ((int)h.getVertices().size(), 8, "Hexagon has 8 vertices");
        runner.EXPECT_GT(h.area(), 0.0, "Hexagon area is positive");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ Array ===" << endl;
    {
        Array<int> arr;
        runner.EXPECT_EQ((int)arr.getSize(), 0, "Empty array size");
        
        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);
        runner.EXPECT_EQ((int)arr.getSize(), 3, "Array size after push_back");
        runner.EXPECT_EQ(arr[0], 1, "Array element access 0");
        runner.EXPECT_EQ(arr[1], 2, "Array element access 1");
        runner.EXPECT_EQ(arr[2], 3, "Array element access 2");
        
        arr.remove(1);
        runner.EXPECT_EQ((int)arr.getSize(), 2, "Array size after remove");
        runner.EXPECT_EQ(arr[0], 1, "First element after remove");
        runner.EXPECT_EQ(arr[1], 3, "Second element after remove");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ Figure операций ===" << endl;
    {
        Array<shared_ptr<Figure<int>>> figures;
        figures.push_back(make_shared<Triangle<int>>(0, 0, 5));
        figures.push_back(make_shared<Pentagon<int>>(0, 0, 4));
        figures.push_back(make_shared<Hexagon<int>>(0, 0, 3));
        
        runner.EXPECT_EQ((int)figures.getSize(), 3, "Array of figures size");
        
        double total = 0;
        for (size_t i = 0; i < figures.getSize(); ++i) {
            total += static_cast<double>(*figures[i]);
        }
        runner.EXPECT_GT(total, 0.0, "Total area is positive");
    }
    
    cout << "\n=== ТЕСТИРОВАНИЕ разных типов данных ===" << endl;
    {
        Triangle<int> t_int(0, 0, 5);
        Triangle<double> t_double(0.0, 0.0, 5.5);
        Triangle<float> t_float(0.0f, 0.0f, 5.5f);
        
        runner.EXPECT_GT_DOUBLE(t_int.area(), 0.0, "int type area");
        runner.EXPECT_GT_DOUBLE(t_double.area(), 0.0, "double type area");
        runner.EXPECT_GT_DOUBLE(t_float.area(), 0.0, "float type area");
    }
    
    runner.Report();
}

int main() {
    cout << "========================================" << endl;
    cout << "GOOGLE TEST-ПОДОБНЫЕ ТЕСТЫ" << endl;
    cout << "Лабораторная работа 4" << endl;
    cout << "========================================" << endl;
    
    try {
        RunAllTests();
        return 0;
    } catch (const exception& e) {
        cerr << "Исключение: " << e.what() << endl;
        return 1;
    }
}
