#include "DynamicArray.h"
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Конструктор
DynamicArray::DynamicArray(int arraySize) {
    if (arraySize <= 0) {
        size = 1; // Минимальный размер
    } else {
        size = arraySize;
    }
    
    data = new int[size];
    // Инициализируем массив нулями
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

// Конструктор копирования
DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
    
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

// Деструктор
DynamicArray::~DynamicArray() {
    delete[] data;
}

// Вывод всех значений массива
void DynamicArray::print() const {
    cout << "Массив [размер: " << size << "]: ";
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Проверка значения на принадлежность к промежутку [-100, 100]
bool DynamicArray::isValidValue(int value) const {
    return (value >= -100 && value <= 100);
}

// Проверка индекса на валидность
bool DynamicArray::isValidIndex(int index) const {
    return (index >= 0 && index < size);
}

// Сеттер - установка значения по индексу
bool DynamicArray::setValue(int index, int value) {
    if (!isValidIndex(index)) {
        cout << "Ошибка: индекс " << index << " выходит за границы массива!" << endl;
        return false;
    }
    
    if (!isValidValue(value)) {
        cout << "Ошибка: значение " << value << " должно быть в диапазоне [-100, 100]!" << endl;
        return false;
    }
    
    data[index] = value;
    return true;
}

// Геттер - получение значения по индексу
bool DynamicArray::getValue(int index, int& value) const {
    if (!isValidIndex(index)) {
        cout << "Ошибка: индекс " << index << " выходит за границы массива!" << endl;
        return false;
    }
    
    value = data[index];
    return true;
}

// Добавление значения в конец массива
void DynamicArray::append(int value) {
    if (!isValidValue(value)) {
        cout << "Ошибка: значение " << value << " должно быть в диапазоне [-100, 100]!" << endl;
        return;
    }
    
    // Создаем новый массив на 1 элемент больше
    int newSize = size + 1;
    int* newData = new int[newSize];
    
    // Копируем старые данные
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    
    // Добавляем новое значение
    newData[size] = value;
    
    // Освобождаем старую память и обновляем указатель и размер
    delete[] data;
    data = newData;
    size = newSize;
    
    cout << "Значение " << value << " успешно добавлено в конец массива." << endl;
}

// Операция сложения массивов
DynamicArray& DynamicArray::add(const DynamicArray& other) {
    int maxSize = (size > other.size) ? size : other.size;
    
    for (int i = 0; i < maxSize; i++) {
        int value1 = (i < size) ? data[i] : 0;
        int value2 = (i < other.size) ? other.data[i] : 0;
        int result = value1 + value2;
        
        // Проверяем результат на валидность и устанавливаем только для существующих индексов
        if (i < size) {
            if (isValidValue(result)) {
                data[i] = result;
            } else {
                cout << "Предупреждение: результат сложения " << result 
                     << " выходит за допустимый диапазон! Элемент не изменен." << endl;
            }
        }
    }
    
    return *this;
}

// Операция вычитания массивов
DynamicArray& DynamicArray::subtract(const DynamicArray& other) {
    int maxSize = (size > other.size) ? size : other.size;
    
    for (int i = 0; i < maxSize; i++) {
        int value1 = (i < size) ? data[i] : 0;
        int value2 = (i < other.size) ? other.data[i] : 0;
        int result = value1 - value2;
        
        // Проверяем результат на валидность и устанавливаем только для существующих индексов
        if (i < size) {
            if (isValidValue(result)) {
                data[i] = result;
            } else {
                cout << "Предупреждение: результат вычитания " << result 
                     << " выходит за допустимый диапазон! Элемент не изменен." << endl;
            }
        }
    }
    
    return *this;
}

// Реализация методов ExtendedDynamicArray

// Конструктор ExtendedDynamicArray
ExtendedDynamicArray::ExtendedDynamicArray(int arraySize) : DynamicArray(arraySize) {}

// Конструктор копирования ExtendedDynamicArray
ExtendedDynamicArray::ExtendedDynamicArray(const DynamicArray& other) : DynamicArray(other) {}

// Вычисление среднего значения
double ExtendedDynamicArray::calculateAverage() const {
    if (getSize() == 0) {
        return 0.0;
    }
    
    int sum = 0;
    int value;
    for (int i = 0; i < getSize(); i++) {
        getValue(i, value);
        sum += value;
    }
    
    return static_cast<double>(sum) / getSize();
}

// Вычисление медианного значения
double ExtendedDynamicArray::calculateMedian() const {
    int arraySize = getSize();
    if (arraySize == 0) {
        return 0.0;
    }
    
    // Создаем временный массив для сортировки
    int* tempArray = new int[arraySize];
    int value;
    for (int i = 0; i < arraySize; i++) {
        getValue(i, value);
        tempArray[i] = value;
    }
    
    // Сортируем массив
    sort(tempArray, tempArray + arraySize);
    
    double median;
    if (arraySize % 2 == 0) {
        // Четное количество элементов - среднее двух центральных
        median = (tempArray[arraySize/2 - 1] + tempArray[arraySize/2]) / 2.0;
    } else {
        // Нечетное количество элементов - центральный элемент
        median = tempArray[arraySize/2];
    }
    
    delete[] tempArray;
    return median;
}

// Нахождение наименьшего элемента
int ExtendedDynamicArray::findMin() const {
    if (getSize() == 0) {
        return 0;
    }
    
    int minValue;
    getValue(0, minValue);
    
    int value;
    for (int i = 1; i < getSize(); i++) {
        getValue(i, value);
        if (value < minValue) {
            minValue = value;
        }
    }
    
    return minValue;
}

// Нахождение наибольшего элемента
int ExtendedDynamicArray::findMax() const {
    if (getSize() == 0) {
        return 0;
    }
    
    int maxValue;
    getValue(0, maxValue);
    
    int value;
    for (int i = 1; i < getSize(); i++) {
        getValue(i, value);
        if (value > maxValue) {
            maxValue = value;
        }
    }
    
    return maxValue;
}