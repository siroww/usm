#include "Header/Side.h"

// Конструктор по умолчанию: длина стороны равна 0.
Side::Side()
    : sideLength(0.0) {
}

// Конструктор с проверкой на неотрицательную длину стороны.
Side::Side(double side)
    : sideLength(side >= 0.0 ? side : 0.0) {
}

// Установить длину стороны квадрата.
void Side::setSide(double side) {
    sideLength = (side >= 0.0 ? side : 0.0);
}

// Получить длину стороны квадрата.
double Side::getSide() const {
    return sideLength;
}
