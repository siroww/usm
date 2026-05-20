#pragma once
#include <iostream>
#include <string>

template <typename T1, typename T2, typename T3>
class Employee {
private:
    T1 name;    // Имя сотрудника (обычно std::string)
    T2 field2;  // Зарплата (double) ИЛИ Номер кабинета (int)
    T3 field3;  // Адрес (std::string) ИЛИ Телефон (const char*)

public:
    // Конструктор
    Employee(T1 name, T2 field2, T3 field3);
    
    // Функция печати
    void print() const;
};

// Реализация конструктора
template <typename T1, typename T2, typename T3>
Employee<T1, T2, T3>::Employee(T1 name, T2 field2, T3 field3)
    : name(name), field2(field2), field3(field3) {}

// Реализация функции печати
template <typename T1, typename T2, typename T3>
void Employee<T1, T2, T3>::print() const {
    std::cout << "Сотрудник: " << name
              << ", Параметр 1: " << field2
              << ", Параметр 2: " << field3 << "\n";
}