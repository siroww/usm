#include "Header/Cube.h"

// Конструктор куба по умолчанию.
Cube::Cube()
    : Square(), wallThickness(0.0) {
}

// Конструктор куба с заданной длиной стороны и толщиной стенок.
Cube::Cube(double side, double thickness)
    : Square(side), wallThickness(thickness >= 0.0 ? thickness : 0.0) {
}

// Установить толщину стенок куба.
void Cube::setThickness(double thickness) {
    wallThickness = (thickness >= 0.0 ? thickness : 0.0);
}

// Получить толщину стенок куба.
double Cube::getThickness() const {
    return wallThickness;
}

// Вычислить внутреннюю длину стороны куба с учетом толщины стенок.
double Cube::innerSide() const {
    double inner = getSide() - 2.0 * wallThickness;
    return (inner > 0.0 ? inner : 0.0);
}

// Вычислить внутренний объем куба для воды.
double Cube::volume() const {
    double inner = innerSide();
    return inner * inner * inner;
}
