// Лабораторная работа №3. Перегрузка операций
//
// Составить описание класса для объектов — векторов, задаваемых координатами концов
// в трехмерном пространстве. Обеспечить операции сложения и вычитания векторов с получением
// нового вектора (суммы или разности), вычисления скалярного произведения двух векторов,
// длины вектора, косинуса угла между векторами.

#include <iostream>
#include "Vector3D.h"
#include "VectorFunctions.h"
#include <windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Создаем два вектора
    Vector3D v1(3.0, 4.0, 0.0);
    Vector3D v2(1.0, 2.0, 3.0);

    // Сложение
    Vector3D vSum = v1 + v2;
    std::cout << "Summa vectorov: ";
    vSum.print();
    std::cout << std::endl;

    // Вычитание
    Vector3D vDiff = v1 - v2;
    std::cout << "Raznost vectorov: ";
    vDiff.print();
    std::cout << std::endl;

    // Скалярное произведение
    std::cout << "Skalyarnoe proizvedenie: " << v1.dotProduct(v2) << std::endl;

    // Длина первого вектора
    std::cout << "Dlina pervogo vectora: " << v1.length() << std::endl;

    // Косинус угла
    std::cout << "Cosinus ugla mezhdu nimi: " << v1.cosBetween(v2) << std::endl;

    return 0;
}