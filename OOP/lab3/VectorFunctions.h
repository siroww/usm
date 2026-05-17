#pragma once

#include "Vector3D.h"

// Конструктор по умолчанию
Vector3D::Vector3D() : x(0), y(0), z(0) {}

// Конструктор с параметрами
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

// Реализация сложения: создаем новый вектор из сумм координат
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

// Реализация вычитания
Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

// Формула скалярного произведения: x1*x2 + y1*y2 + z1*z2
double Vector3D::dotProduct(const Vector3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Формула длины: корень из суммы квадратов координат
double Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Косинус угла: скалярное произведение деленное на произведение длин
double Vector3D::cosBetween(const Vector3D& other) const {
    double lengthsProduct = this->length() * other.length();
    if (lengthsProduct == 0) return 0; // Защита от деления на ноль
    return dotProduct(other) / lengthsProduct;
}

// Вывод координат вектора
void Vector3D::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")";
}
