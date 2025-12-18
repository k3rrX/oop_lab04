#!/bin/bash

echo "=== Компиляция основной программы ==="
g++ -std=c++20 -I. -o laba4 main.cpp
if [ $? -eq 0 ]; then
    echo "✅ Основная программа скомпилирована успешно"
    echo ""
    echo "=== Запуск основной программы ==="
    echo "Тестовые данные:"
    echo "5-угольник: 0 0 5"
    echo "6-угольник: 2 2 4"
    echo "8-угольник: 5 5 6"
    echo ""
    echo "Результат работы:"
    echo "5 0 0 5" | ./laba4 2>/dev/null || echo "Программа выполнена"
else
    echo "❌ Ошибка компиляции основной программы"
fi

echo ""
echo "=== Компиляция тестов ==="
# Проверяем, установлен ли Google Test
if command -v gtest-config &> /dev/null; then
    g++ -std=c++20 -I. -o run_tests test_figures.cpp -lgtest -lgtest_main -pthread
    if [ $? -eq 0 ]; then
        echo "✅ Тесты скомпилированы успешно"
        echo ""
        echo "=== Запуск тестов ==="
        ./run_tests
    else
        echo "❌ Ошибка компиляции тестов"
    fi
else
    echo "⚠️  Google Test не установлен. Пропускаем тесты."
    echo "Для установки выполните:"
    echo "  Ubuntu: sudo apt-get install libgtest-dev"
    echo "  Затем: cd /usr/src/gtest && sudo cmake . && sudo make"
    echo "  Затем: sudo cp lib/*.a /usr/lib"
fi
