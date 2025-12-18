#!/bin/bash

echo "=========================================="
echo "Лабораторная работа 4 - Сборка и тестирование"
echo "=========================================="

# Создаем вывод с цветами
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${YELLOW}=== Шаг 1: Проверка файлов ===${NC}"
ls -la *.cpp *.h

echo -e "\n${YELLOW}=== Шаг 2: Компиляция основной программы ===${NC}"
g++ -std=c++20 -I. -o laba4.exe main.cpp
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✅ Основная программа скомпилирована${NC}"
else
    echo -e "${RED}❌ Ошибка компиляции основной программы${NC}"
    exit 1
fi

echo -e "\n${YELLOW}=== Шаг 3: Компиляция тестов ===${NC}"
# Проверяем, есть ли Google Test
if [ -f "test_figures.cpp" ]; then
    # Для MinGW в Windows может потребоваться другой подход
    g++ -std=c++20 -I. -o run_tests.exe test_figures.cpp -lgtest -lgtest_main -lpthread 2>&1
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}✅ Тесты скомпилированы${NC}"
        
        echo -e "\n${YELLOW}=== Шаг 4: Запуск тестов ===${NC}"
        ./run_tests.exe
    else
        echo -e "${YELLOW}⚠️  Не удалось скомпилировать тесты с Google Test${NC}"
        echo "Пробуем простые тесты..."
        
        # Создаем простые тесты
        cat > simple_test.cpp << 'SIMPLE'
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
SIMPLE
        
        g++ -std=c++20 -I. -o simple_test.exe simple_test.cpp
        if [ $? -eq 0 ]; then
            ./simple_test.exe
        fi
    fi
else
    echo -e "${YELLOW}⚠️  Файл test_figures.cpp не найден${NC}"
fi

echo -e "\n${YELLOW}=== Шаг 5: Демонстрация работы ===${NC}"
echo "Запуск основной программы с тестовыми данными..."
echo "Входные данные:"
echo "0 0 5"
echo "2 2 4" 
echo "5 5 6"
echo ""
echo "Результат:"

# Создаем временный файл с входными данными
cat > input.txt << INPUT
0 0 5
2 2 4
5 5 6
INPUT

./laba4.exe < input.txt
rm -f input.txt

echo -e "\n${GREEN}✅ Сборка и тестирование завершены!${NC}"
echo "Для запуска программы: ./laba4.exe"
if [ -f "run_tests.exe" ]; then
    echo "Для запуска тестов: ./run_tests.exe"
fi
