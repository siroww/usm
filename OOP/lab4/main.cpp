#include <iostream>
#include <list>
#include <string>
#include <windows.h>
#include "employee.h"

int main() {
    // Настройка кодировки для корректного вывода кириллицы в Windows
    SetConsoleOutputCP(CP_UTF8);

    // ВАРИАНТ 1: Сотрудник (string), Зарплата (double), Адрес (string)
    using EmpType1 = Employee<std::string, double, std::string>;
    std::list<EmpType1> empList1;

    empList1.push_back(EmpType1("Иванов И.И.", 75000.50, "ул. Ленина, д. 10"));
    empList1.push_back(EmpType1("Петров П.П.", 90000.00, "ул. Гагарина, д. 5"));
    empList1.push_back(EmpType1("Сидоров С.С.", 65000.25, "ул. Пушкина, д. 12"));

    std::cout << "Список 1 (Сотрудник, Зарплата, Адрес):\n";
    for (const auto& emp : empList1)
        emp.print();


    // ВАРИАНТ 2: Сотрудник (string), Номер кабинета (int), Телефон (const char*)
    using EmpType2 = Employee<std::string, int, const char*>;
    std::list<EmpType2> empList2;

    empList2.push_back(EmpType2("Алексеев А.А.", 404, "+7-999-111-22-33"));
    empList2.push_back(EmpType2("Борисов Б.Б.", 201, "+7-999-444-55-66"));
    empList2.push_back(EmpType2("Владимиров В.В.", 315, "+7-999-777-88-99"));

    std::cout << "\nСписок 2 (Сотрудник, Номер кабинета, Телефон):\n";
    for (const auto& emp : empList2)
        emp.print();


    // ВСТАВКА нового элемента в первый список (Операция вставки по заданию)
    auto it = empList1.begin();
    std::advance(it, 1); // Сдвигаем итератор на позицию 1 (после первого элемента)
    
    // Вставляем нового сотрудника
    empList1.insert(it, EmpType1("Новиков Н.Н.", 80000.00, "ул. Новая, д. 1"));

    std::cout << "\nПосле вставки в Список 1:\n";
    for (const auto& emp : empList1)
        emp.print();

    return 0;
}