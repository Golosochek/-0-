// all_in_one.cpp
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

// Вспомогательная функция для получения текущей даты и времени
string getCurrentDateTime() {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    
    stringstream ss;
    ss << 1900 + localTime->tm_year << "_"
       << setw(2) << setfill('0') << localTime->tm_mon + 1 << "_"
       << setw(2) << setfill('0') << localTime->tm_mday << "_"
       << setw(2) << setfill('0') << localTime->tm_hour << "_"
       << setw(2) << setfill('0') << localTime->tm_min << "_"
       << setw(2) << setfill('0') << localTime->tm_sec;
    
    return ss.str();
}

class DynamicArray {
private:
    int* data;      // Указатель на данные массива
    int size;       // Размер массива

public:
    // Конструктор, получающий размер массива
    DynamicArray(int arraySize) {
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
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        data = new int[size];
        
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Деструктор
    virtual ~DynamicArray() {
        delete[] data;
    }

    // Функция вывода всех значений массива
    virtual void print() const {
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

    // Сеттер - установка значения по индексу
    bool setValue(int index, int value) {
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
    bool getValue(int index, int& value) const {
        if (!isValidIndex(index)) {
            cout << "Ошибка: индекс " << index << " выходит за границы массива!" << endl;
            return false;
        }
        
        value = data[index];
        return true;
    }

    // Добавление значения в конец массива
    void append(int value) {
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
    DynamicArray& add(const DynamicArray& other) {
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
    DynamicArray& subtract(const DynamicArray& other) {
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

    // Вспомогательные методы
    int getSize() const { return size; }
    
    // Виртуальный метод для экспорта данных
    virtual void exportToFile() const {
        cout << "Экспорт данных массива в консоль:" << endl;
        print();
    }
    
private:
    // Проверка значения на принадлежность к промежутку [-100, 100]
    bool isValidValue(int value) const {
        return (value >= -100 && value <= 100);
    }
    
    // Проверка индекса на валидность
    bool isValidIndex(int index) const {
        return (index >= 0 && index < size);
    }
};

// Новый класс, наследующий от DynamicArray
class ExtendedDynamicArray : public DynamicArray {
public:
    // Конструкторы
    ExtendedDynamicArray(int arraySize) : DynamicArray(arraySize) {}
    
    ExtendedDynamicArray(const DynamicArray& other) : DynamicArray(other) {}
    
    // Новые методы
    double calculateAverage() const {
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
    
    double calculateMedian() const {
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
    
    int findMin() const {
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
    
    int findMax() const {
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
};

// Класс для вывода в txt файл
class ArrTxt : public DynamicArray {
public:
    // Конструкторы
    ArrTxt(int arraySize) : DynamicArray(arraySize) {}
    
    ArrTxt(const DynamicArray& other) : DynamicArray(other) {}
    
    // Переопределение метода экспорта
    virtual void exportToFile() const override {
        string fileName = "array_" + getCurrentDateTime() + ".txt";
        
        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cerr << "Ошибка при создании файла: " << fileName << endl;
            return;
        }
        
        outFile << "=== Динамический массив (TXT формат) ===" << endl;
        outFile << "Дата создания: " << getCurrentDateTime() << endl;
        outFile << "Размер массива: " << getSize() << endl;
        outFile << "Элементы массива:" << endl;
        
        for (int i = 0; i < getSize(); i++) {
            int value;
            getValue(i, value);
            outFile << "[" << i << "] = " << value << endl;
        }
        
        outFile << "=== Конец данных ===" << endl;
        outFile.close();
        
        cout << "Данные успешно экспортированы в файл: " << fileName << endl;
    }
};

// Класс для вывода в csv файл
class ArrCSV : public DynamicArray {
public:
    // Конструкторы
    ArrCSV(int arraySize) : DynamicArray(arraySize) {}
    
    ArrCSV(const DynamicArray& other) : DynamicArray(other) {}
    
    // Переопределение метода экспорта
    virtual void exportToFile() const override {
        string fileName = "array_" + getCurrentDateTime() + ".csv";
        
        ofstream outFile(fileName);
        if (!outFile.is_open()) {
            cerr << "Ошибка при создании файла: " << fileName << endl;
            return;
        }
        
        // Заголовок CSV
        outFile << "Index,Value" << endl;
        
        // Данные
        for (int i = 0; i < getSize(); i++) {
            int value;
            getValue(i, value);
            outFile << i << "," << value << endl;
        }
        
        outFile.close();
        
        cout << "Данные успешно экспортированы в файл: " << fileName << endl;
    }
};

// Функция для демонстрации полиморфизма
void exportArray(const DynamicArray& arr) {
    cout << endl << "--- Экспорт массива ---" << endl;
    arr.exportToFile();
}

int main() {
    cout << "=== Демонстрация работы класса DynamicArray ===" << endl << endl;

    // ... (основной код из main.cpp, который я присылал ранее) ...
    // Вставьте сюда весь main() из предыдущего ответа, начиная с создания arr1

    // Для краткости покажу только часть, добавьте весь код
    DynamicArray arr1(3);
    arr1.setValue(0, 10);
    arr1.setValue(1, -50);
    arr1.setValue(2, 100);
    
    // ... остальной код ...

    return 0;
}