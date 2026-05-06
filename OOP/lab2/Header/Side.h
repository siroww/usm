#pragma once

// Класс Side хранит длину стороны квадрата.
class Side {
protected:
    double sideLength; // длина стороны квадрата

public:
    Side();               // конструктор по умолчанию
    explicit Side(double side); // конструктор с длиной стороны

    void setSide(double side); // задать длину стороны
    double getSide() const;    // получить длину стороны
};
