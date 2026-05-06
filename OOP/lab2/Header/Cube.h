#pragma once

#include "Square.h"

// Класс Cube расширяет Square, добавляя толщину стенок и объем.
class Cube : public Square {
private:
    double wallThickness; // толщина стенок куба

public:
    Cube();
    Cube(double side, double thickness);

    void setThickness(double thickness); // задать толщину стенок
    double getThickness() const;         // получить толщину стенок

    double innerSide() const; // вычислить внутреннюю длину стороны
    double volume() const;    // вычислить внутренний объем воды
};
