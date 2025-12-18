#include <gtest/gtest.h>
#include <memory>
#include <cmath>
#include "Point.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Array.h"

using namespace std;

// ================== ТЕСТЫ ДЛЯ Point ==================
TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.getX(), 0);
    EXPECT_EQ(p.getY(), 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.getX(), 3.5);
    EXPECT_DOUBLE_EQ(p.getY(), 4.2);
}

TEST(PointTest, DistanceCalculation) {
    Point<int> p1(0, 0);
    Point<int> p2(3, 4);
    EXPECT_DOUBLE_EQ(p1.distanceTo(p2), 5.0);
}

// ================== ТЕСТЫ ДЛЯ Triangle (5-угольник) ==================
TEST(TriangleTest, CreationAndArea) {
    Triangle<int> t(0, 0, 5);
    EXPECT_GT(t.area(), 0);
    
    // Проверка, что создано 5 вершин
    EXPECT_EQ(t.getVertices().size(), 5);
}

TEST(TriangleTest, GeometricCenter) {
    Triangle<int> t(10, 10, 5);
    auto center = t.geometricCenter();
    
    // Центр должен быть близок к (10, 10)
    EXPECT_NEAR(center.getX(), 10, 0.1);
    EXPECT_NEAR(center.getY(), 10, 0.1);
}

TEST(TriangleTest, CopyConstructor) {
    Triangle<int> t1(0, 0, 5);
    Triangle<int> t2 = t1;
    
    EXPECT_TRUE(t1 == t2);
}

TEST(TriangleTest, Clone) {
    auto t1 = make_shared<Triangle<int>>(0, 0, 5);
    auto t2 = t1->clone();
    
    EXPECT_TRUE(*t1 == *t2);
    EXPECT_NE(t1.get(), t2.get()); // Указатели разные
}

// ================== ТЕСТЫ ДЛЯ Pentagon (6-угольник) ==================
TEST(PentagonTest, CreationAndArea) {
    Pentagon<int> p(0, 0, 5);
    EXPECT_GT(p.area(), 0);
    EXPECT_EQ(p.getVertices().size(), 6);
}

TEST(PentagonTest, DoubleType) {
    Pentagon<double> p(0.0, 0.0, 5.5);
    EXPECT_GT(p.area(), 0);
}

// ================== ТЕСТЫ ДЛЯ Hexagon (8-угольник) ==================
TEST(HexagonTest, CreationAndArea) {
    Hexagon<int> h(0, 0, 5);
    EXPECT_GT(h.area(), 0);
    EXPECT_EQ(h.getVertices().size(), 8);
}

// ================== ТЕСТЫ ДЛЯ Array ==================
TEST(ArrayTest, DefaultConstructor) {
    Array<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
    EXPECT_EQ(arr.getCapacity(), 0);
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, RemoveElement) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.remove(1); // Удаляем второй элемент
    
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, MoveSemantics) {
    Array<shared_ptr<Figure<int>>> arr;
    auto fig = make_shared<Triangle<int>>(0, 0, 5);
    
    // Проверяем перемещение
    arr.push_back(move(fig));
    EXPECT_EQ(arr.getSize(), 1);
    EXPECT_NE(arr[0], nullptr);
}

TEST(ArrayTest, FigureArrayOperations) {
    Array<shared_ptr<Figure<int>>> figures;
    
    figures.push_back(make_shared<Triangle<int>>(0, 0, 5));
    figures.push_back(make_shared<Pentagon<int>>(2, 2, 4));
    figures.push_back(make_shared<Hexagon<int>>(5, 5, 6));
    
    EXPECT_EQ(figures.getSize(), 3);
    
    // Проверяем площади
    double totalArea = 0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        totalArea += figures[i]->area();
    }
    EXPECT_GT(totalArea, 0);
    
    // Удаляем фигуру
    figures.remove(1);
    EXPECT_EQ(figures.getSize(), 2);
}

// ================== ТЕСТЫ ДЛЯ Figure операций ==================
TEST(FigureTest, DoubleConversion) {
    Triangle<int> t(0, 0, 5);
    double area = static_cast<double>(t);
    EXPECT_GT(area, 0);
}

TEST(FigureTest, Comparison) {
    Triangle<int> t1(0, 0, 5);
    Triangle<int> t2(0, 0, 5);
    Triangle<int> t3(10, 10, 5);
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(FigureTest, TotalAreaCalculation) {
    Array<shared_ptr<Figure<int>>> figures;
    figures.push_back(make_shared<Triangle<int>>(0, 0, 5));
    figures.push_back(make_shared<Pentagon<int>>(0, 0, 5));
    figures.push_back(make_shared<Hexagon<int>>(0, 0, 5));
    
    double total = 0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        total += static_cast<double>(*figures[i]);
    }
    
    EXPECT_GT(total, 0);
}

// ================== ИНТЕГРАЦИОННЫЕ ТЕСТЫ ==================
TEST(IntegrationTest, CompleteWorkflow) {
    // Создаем массив фигур
    Array<shared_ptr<Figure<double>>> figures;
    
    // Добавляем разные фигуры
    figures.push_back(make_shared<Triangle<double>>(0.0, 0.0, 5.0));
    figures.push_back(make_shared<Pentagon<double>>(1.0, 1.0, 4.0));
    figures.push_back(make_shared<Hexagon<double>>(2.0, 2.0, 3.0));
    
    // Проверяем количество
    EXPECT_EQ(figures.getSize(), 3);
    
    // Проверяем, что все фигуры созданы
    for (size_t i = 0; i < figures.getSize(); ++i) {
        EXPECT_NE(figures[i], nullptr);
        EXPECT_GT(figures[i]->area(), 0);
    }
    
    // Клонируем первую фигуру
    auto cloned = figures[0]->clone();
    EXPECT_TRUE(*figures[0] == *cloned);
    
    // Удаляем среднюю фигуру
    figures.remove(1);
    EXPECT_EQ(figures.getSize(), 2);
    
    // Проверяем оставшиеся фигуры
    EXPECT_GT(figures[0]->area(), 0);
    EXPECT_GT(figures[1]->area(), 0);
}

// Тест на разные типы данных
TEST(TypeTest, DifferentScalarTypes) {
    // int
    Triangle<int> t_int(0, 0, 5);
    EXPECT_GT(t_int.area(), 0);
    
    // double
    Triangle<double> t_double(0.0, 0.0, 5.5);
    EXPECT_GT(t_double.area(), 0);
    
    // float
    Triangle<float> t_float(0.0f, 0.0f, 5.5f);
    EXPECT_GT(t_float.area(), 0);
}

// Тест на обработку ошибок
TEST(ErrorTest, ArrayBounds) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    
    // Должно выбрасывать исключение при выходе за границы
    EXPECT_THROW(arr[5], std::out_of_range);
    EXPECT_THROW(arr.remove(5), std::out_of_range);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}