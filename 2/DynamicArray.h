#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <string>

class DynamicArray {
private:
    int* data;      // Указатель на данные массива
    int size;       // Размер массива

public:
    // Конструктор, получающий размер массива
    DynamicArray(int arraySize);
    
    // Конструктор копирования
    DynamicArray(const DynamicArray& other);
    
    // Деструктор
    virtual ~DynamicArray();  // Сделал виртуальным

    // Функция вывода всех значений массива
    virtual void print() const;

    // Сеттер - установка значения по индексу
    bool setValue(int index, int value);

    // Геттер - получение значения по индексу
    bool getValue(int index, int& value) const;

    // Добавление значения в конец массива
    void append(int value);

    // Операция сложения массивов
    DynamicArray& add(const DynamicArray& other);

    // Операция вычитания массивов
    DynamicArray& subtract(const DynamicArray& other);

    // Вспомогательные методы
    int getSize() const { return size; }
    
    // Виртуальный метод для экспорта данных
    virtual void exportToFile() const;
    
private:
    // Проверка значения на принадлежность к промежутку [-100, 100]
    bool isValidValue(int value) const;
    
    // Проверка индекса на валидность
    bool isValidIndex(int index) const;
};

// Новый класс, наследующий от DynamicArray
class ExtendedDynamicArray : public DynamicArray {
public:
    // Конструкторы
    ExtendedDynamicArray(int arraySize);
    ExtendedDynamicArray(const DynamicArray& other);
    
    // Новые методы
    double calculateAverage() const;        // Вычисление среднего значения
    double calculateMedian() const;         // Вычисление медианного значения
    int findMin() const;                    // Нахождение наименьшего элемента
    int findMax() const;                    // Нахождение наибольшего элемента
};

// Класс для вывода в txt файл
class ArrTxt : public DynamicArray {
public:
    // Конструкторы
    ArrTxt(int arraySize);
    ArrTxt(const DynamicArray& other);
    
    // Переопределение метода экспорта
    virtual void exportToFile() const override;
};

// Класс для вывода в csv файл
class ArrCSV : public DynamicArray {
public:
    // Конструкторы
    ArrCSV(int arraySize);
    ArrCSV(const DynamicArray& other);
    
    // Переопределение метода экспорта
    virtual void exportToFile() const override;
};

#endif