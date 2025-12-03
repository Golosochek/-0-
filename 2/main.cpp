#include <iostream>
#include "DynamicArray.h"

using namespace std;

// Функция для демонстрации полиморфизма
void exportArray(const DynamicArray& arr) {
    cout << endl << "--- Экспорт массива ---" << endl;
    arr.exportToFile();
}

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

    // Задание 5: Тестирование ExtendedDynamicArray
    cout << endl << "=== Демонстрация работы класса ExtendedDynamicArray ===" << endl << endl;
    
    // Создание расширенного массива
    ExtendedDynamicArray extArr1(5);
    extArr1.setValue(0, 10);
    extArr1.setValue(1, 20);
    extArr1.setValue(2, 30);
    extArr1.setValue(3, 40);
    extArr1.setValue(4, 50);
    
    cout << "Расширенный массив 1: ";
    extArr1.print();
    
    // Тестирование новых методов
    cout << "Среднее значение: " << extArr1.calculateAverage() << endl;
    cout << "Медианное значение: " << extArr1.calculateMedian() << endl;
    cout << "Наименьший элемент: " << extArr1.findMin() << endl;
    cout << "Наибольший элемент: " << extArr1.findMax() << endl;
    
    cout << endl << "--- Тестирование с другим массивом ---" << endl;
    
    ExtendedDynamicArray extArr2(6);
    extArr2.setValue(0, 15);
    extArr2.setValue(1, -10);
    extArr2.setValue(2, 25);
    extArr2.setValue(3, 5);
    extArr2.setValue(4, -5);
    extArr2.setValue(5, 35);
    
    cout << "Расширенный массив 2: ";
    extArr2.print();
    
    cout << "Среднее значение: " << extArr2.calculateAverage() << endl;
    cout << "Медианное значение: " << extArr2.calculateMedian() << endl;
    cout << "Наименьший элемент: " << extArr2.findMin() << endl;
    cout << "Наибольший элемент: " << extArr2.findMax() << endl;
    
    cout << endl << "--- Тестирование с нечетным количеством элементов ---" << endl;
    
    ExtendedDynamicArray extArr3(3);
    extArr3.setValue(0, 10);
    extArr3.setValue(1, 5);
    extArr3.setValue(2, 15);
    
    cout << "Расширенный массив 3: ";
    extArr3.print();
    
    cout << "Среднее значение: " << extArr3.calculateAverage() << endl;
    cout << "Медианное значение: " << extArr3.calculateMedian() << endl;
    cout << "Наименьший элемент: " << extArr3.findMin() << endl;
    cout << "Наибольший элемент: " << extArr3.findMax() << endl;

    // Демонстрация полиморфизма из ПЗ5
    cout << endl << "=== Демонстрация полиморфизма (ПЗ5) ===" << endl << endl;
    
    // Создание массива в txt формате
    ArrTxt txtArr(4);
    txtArr.setValue(0, 10);
    txtArr.setValue(1, 20);
    txtArr.setValue(2, 30);
    txtArr.setValue(3, 40);
    
    cout << "Массив ArrTxt: ";
    txtArr.print();
    
    // Создание массива в csv формате
    ArrCSV csvArr(3);
    csvArr.setValue(0, 5);
    csvArr.setValue(1, 15);
    csvArr.setValue(2, 25);
    
    cout << "Массив ArrCSV: ";
    csvArr.print();
    
    // Использование функции полиморфизма
    cout << endl << "1. Экспорт через полиморфизм:" << endl;
    exportArray(txtArr);  // Будет вызван метод ArrTxt::exportToFile()
    exportArray(csvArr);  // Будет вызван метод ArrCSV::exportToFile()
    
    // Использование указателей для демонстрации полиморфизма (как в примере из задания)
    cout << endl << "2. Экспорт через указатели (как в примере задания):" << endl;
    DynamicArray* arrays[3];
    
    // Создаем объекты разных типов
    arrays[0] = new DynamicArray(2);
    arrays[0]->setValue(0, 100);
    arrays[0]->setValue(1, -50);
    
    arrays[1] = new ArrTxt(3);
    arrays[1]->setValue(0, 1);
    arrays[1]->setValue(1, 2);
    arrays[1]->setValue(2, 3);
    
    arrays[2] = new ArrCSV(4);
    arrays[2]->setValue(0, 10);
    arrays[2]->setValue(1, 20);
    arrays[2]->setValue(2, 30);
    arrays[2]->setValue(3, 40);
    
    // Экспорт всех массивов через полиморфизм
    for (int i = 0; i < 3; i++) {
        cout << endl << "Массив " << i + 1 << ":" << endl;
        arrays[i]->print();
        arrays[i]->exportToFile();  // Вызовется правильная реализация
        delete arrays[i];
    }
    
    // Экспорт ExtendedDynamicArray
    cout << endl << "3. Экспорт ExtendedDynamicArray:" << endl;
    exportArray(extArr1);

    return 0;
}