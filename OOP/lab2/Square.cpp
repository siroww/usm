#include "Header/Square.h"

// Конструктор квадрата по умолчанию.
Square::Square()
    : Side() {
}

// Конструктор квадрата с заданной длиной стороны.
Square::Square(double side)
    : Side(side) {
}

// Вычислить площадь квадрата.
double Square::area() const {
    return getSide() * getSide();
}
