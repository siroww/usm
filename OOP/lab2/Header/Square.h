#pragma once

#include "Side.h"

// Класс Square расширяет Side и может вычислять площадь.
class Square : public Side {
public:
    Square();               // конструктор по умолчанию
    explicit Square(double side); // конструктор с длиной стороны

    double area() const; // вычислить площадь квадрата
};
