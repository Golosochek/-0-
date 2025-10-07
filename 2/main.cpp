#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main() {
    cout << "=== Демонстрация работы класса DynamicArray ===" << endl << endl;

    // Задание 1: Создание массива и базовые операции
    cout << "1. Создание массивов и базовые операции:" << endl;
    DynamicArray arr1(3);
    DynamicArray arr2(5);
    
    cout << "Исходный массив 1: ";
    arr1.print();
    
    cout << "Исходный массив 2: ";
    arr2.print();
    
    // Тестирование сеттера и геттера
    cout << endl << "2. Тестирование сеттера и геттера:" << endl;
    arr1.setValue(0, 10);
    arr1.setValue(1, -50);
    arr1.setValue(2, 100);
    
    // Попытка установить невалидные значения
    arr1.setValue(0, 150);  // Слишком большое значение
    arr1.setValue(5, 50);   // Невалидный индекс
    
    cout << "Массив 1 после установки значений: ";
    arr1.print();
    
    // Тестирование геттера
    int value;
    if (arr1.getValue(1, value)) {
        cout << "Значение по индексу 1: " << value << endl;
    }
    
    // Задание 2: Тестирование конструктора копирования
    cout << endl << "3. Тестирование конструктора копирования:" << endl;
    DynamicArray arr3 = arr1;  // Конструктор копирования
    cout << "Оригинал: ";
    arr1.print();
    cout << "Копия: ";
    arr3.print();
    
    // Задание 3: Добавление элементов в конец
    cout << endl << "4. Добавление элементов в конец массива:" << endl;
    cout << "Массив 2 до добавления: ";
    arr2.print();
    
    arr2.append(25);
    arr2.append(-75);
    arr2.append(101);  // Невалидное значение
    
    cout << "Массив 2 после добавления: ";
    arr2.print();
    
    // Задание 4: Операции сложения и вычитания
    cout << endl << "5. Операции сложения и вычитания массивов:" << endl;
    
    // Подготовка массивов для операций
    DynamicArray arr4(4);
    arr4.setValue(0, 10);
    arr4.setValue(1, 20);
    arr4.setValue(2, 30);
    arr4.setValue(3, 40);
    
    DynamicArray arr5(3);
    arr5.setValue(0, 5);
    arr5.setValue(1, 15);
    arr5.setValue(2, 25);
    
    cout << "Массив 4: ";
    arr4.print();
    cout << "Массив 5: ";
    arr5.print();
    
    // Сложение
    cout << "Сложение массивов (arr4 + arr5):" << endl;
    arr4.add(arr5);
    arr4.print();
    
    // Вычитание
    cout << "Вычитание массивов (arr4 - arr5):" << endl;
    arr4.subtract(arr5);
    arr4.print();
    
    // Тестирование с массивами разного размера
    cout << endl << "6. Операции с массивами разного размера:" << endl;
    DynamicArray arr6(2);
    arr6.setValue(0, 50);
    arr6.setValue(1, 60);
    
    DynamicArray arr7(4);
    arr7.setValue(0, 10);
    arr7.setValue(1, 20);
    arr7.setValue(2, 30);
    arr7.setValue(3, 40);
    
    cout << "Массив 6: ";
    arr6.print();
    cout << "Массив 7: ";
    arr7.print();
    
    cout << "arr6 + arr7: ";
    arr6.add(arr7);
    arr6.print();
    
    cout << "arr7 - arr6: ";
    arr7.subtract(arr6);
    arr7.print();

    return 0;
}