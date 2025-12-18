#include <iostream>
#include <memory>
#include <vector>
#include "Point.h"
#include "Triangle.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Array.h"

using namespace std;

template<typename T>
void printFigureInfo(const Figure<T>& fig) {
    cout << fig << endl;
    cout << "Площадь (через double): " << static_cast<double>(fig) << endl;
    cout << "------------------------" << endl;
}

template<typename T>
double calculateTotalArea(const Array<shared_ptr<Figure<T>>>& figures) {
    double total = 0.0;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        total += figures[i]->area();
    }
    return total;
}

int main() {
    cout << "=== Лабораторная работа 4: Шаблоны классов для геометрических фигур ===" << endl;
    cout << "Вариант: 5-угольник, 6-угольник, 8-угольник" << endl << endl;

    // Массив для базового типа Figure*
    Array<shared_ptr<Figure<int>>> figures;

    // Ввод фигур с консоли
    cout << "Введите данные для 5-угольника (x y радиус): ";
    int x1, y1, r1;
    cin >> x1 >> y1 >> r1;
    auto triangle = make_shared<Triangle<int>>(x1, y1, r1);
    figures.push_back(triangle);

    cout << "Введите данные для 6-угольника (x y радиус): ";
    int x2, y2, r2;
    cin >> x2 >> y2 >> r2;
    auto pentagon = make_shared<Pentagon<int>>(x2, y2, r2);
    figures.push_back(pentagon);

    cout << "Введите данные для 8-угольника (x y радиус): ";
    int x3, y3, r3;
    cin >> x3 >> y3 >> r3;
    auto hexagon = make_shared<Hexagon<int>>(x3, y3, r3);
    figures.push_back(hexagon);

    // Вывод информации о всех фигурах
    cout << "\n=== Информация о всех фигурах ===" << endl;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        cout << "Фигура " << i + 1 << ":" << endl;
        printFigureInfo(*figures[i]);
    }

    // Общая площадь
    cout << "Общая площадь всех фигур: " << calculateTotalArea(figures) << endl;

    // Тестирование операций
    cout << "\n=== Тестирование операций ===" << endl;
    cout << "Сравнение первого и второго пятиугольников: ";
    auto triangle2 = make_shared<Triangle<int>>(x1, y1, r1);
    cout << (*triangle == *triangle2 ? "Равны" : "Не равны") << endl;

    // Удаление фигуры по индексу
    cout << "\nУдаляем фигуру с индексом 1 (6-угольник)..." << endl;
    figures.remove(1);

    cout << "\n=== Фигуры после удаления ===" << endl;
    for (size_t i = 0; i < figures.getSize(); ++i) {
        cout << "Фигура " << i + 1 << ":" << endl;
        printFigureInfo(*figures[i]);
    }

    // Тестирование с разными типами
    cout << "\n=== Тестирование с разными типами ===" << endl;
    
    // С double
    Array<shared_ptr<Figure<double>>> figuresDouble;
    figuresDouble.push_back(make_shared<Triangle<double>>(1.5, 2.5, 3.0));
    figuresDouble.push_back(make_shared<Pentagon<double>>(2.0, 3.0, 4.0));
    
    cout << "Фигуры с типом double:" << endl;
    for (size_t i = 0; i < figuresDouble.getSize(); ++i) {
        printFigureInfo(*figuresDouble[i]);
    }

    // Тестирование массива с конкретными типами
    cout << "\n=== Тестирование Array<Triangle<int>> ===" << endl;
    Array<Triangle<int>> trianglesArray;
    trianglesArray.push_back(Triangle<int>(0, 0, 5));
    trianglesArray.push_back(Triangle<int>(10, 10, 3));
    
    cout << "Массив 5-угольников:" << endl;
    for (size_t i = 0; i < trianglesArray.getSize(); ++i) {
        cout << trianglesArray[i] << endl;
    }

    // Тестирование копирования
    cout << "\n=== Тестирование копирования ===" << endl;
    auto original = make_shared<Triangle<int>>(0, 0, 10);
    auto copy = original->clone();
    
    cout << "Оригинал: " << endl << *original << endl;
    cout << "Копия: " << endl << *copy << endl;
    cout << "Они равны? " << (*original == *copy ? "Да" : "Нет") << endl;

    cout << "\nПрограмма успешно завершена!" << endl;
    
    return 0;
}
