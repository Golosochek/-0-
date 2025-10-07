#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

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
    ~DynamicArray();

    // Функция вывода всех значений массива
    void print() const;

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
    
private:
    // Проверка значения на принадлежность к промежутку [-100, 100]
    bool isValidValue(int value) const;
    
    // Проверка индекса на валидность
    bool isValidIndex(int index) const;
};

#endif