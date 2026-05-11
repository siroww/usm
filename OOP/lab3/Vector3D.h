#pragma once

#include <iostream>
#include <cmath>

class Vector3D {
private:
    double x, y, z; // Координаты вектора

public:
    // Конструкторы
    Vector3D();
    Vector3D(double x, double y, double z);

    // Перегрузка операторов сложения и вычитания
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;

    // Скалярное произведение
    double dotProduct(const Vector3D& other) const;

    // Длина вектора
    double length() const;

    // Косинус угла между векторами
    double cosBetween(const Vector3D& other) const;

    // Метод для получения координат (для вывода)
    void print() const;
};

#endif