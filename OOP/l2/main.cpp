//Создайте иерархию классов Сторона – Квадрат – Куб. Класс Квадрат должен содержать метод для вычисления площади квадрата, а класс Куб метод для вычисления объема куба. При вычислении объема куба учитывать толщину стенок куба. Последние два класса в иерархии должны иметь конструкторы. Создайте метод MAIN, в котором создается 2 куба (т.е. 2 объекта класса Куб), определяется какой из кубов меньший и сколько надо наполнить водой меньших кубов, чтобы заполнить больший. Необходимо также показывать все характеристики создаваемых объектов.

#include <iostream>
#include <string>

using namespace std;

class Side {
protected:
    string name;
    double a; 

public:
    Side(double valA, string valName) : a(valA), name(valName) {}

    virtual void show() const {
        cout << "Ob'ekt: " << name << "\n"
             << "Storona: " << a << " cm" << endl;
    }
};

class Square : public Side {
public:
    Square(double valA, string valName) : Side(valA, valName) {}

    double calculateArea() const {
        return a * a;
    }

    void show() const override {
        Side::show();
        cout << "Ploshad' kvadrata: " << calculateArea() << " cm^2" << endl;
    }
};

class Cube : public Square {
protected:
    double thickness; 

public:
    Cube(double valA, double valT, string valName) 
        : Square(valA, valName), thickness(valT) {}

    double calculateVolume() const {
        // внутреняя сторона куба с учетом толщины стенок
        double innerSide = a - (2 * thickness);
        if (innerSide <= 0) return 0; 
        return innerSide * innerSide * innerSide;
    }

    void show() const override {
        Square::show();
        cout << "Tolshina stenok: " << thickness << " cm\n"
             << "Vnutrenniy ob'em (dlya vody): " << calculateVolume() << " cm^3\n" << endl;
    }

    string getName() const { return name; }
};

int main() {
    // 2 куба (размер, толщина стенок, имя)
    Cube c1(12.0, 0.5, "Kub_A");
    Cube c2(18.0, 1.5, "Kub_B");

    cout << "--- Harakteristiki kubov ---" << endl;
    c1.show();
    c2.show();

    Cube* smaller;
    Cube* bigger;

    if (c1.calculateVolume() < c2.calculateVolume()) {
        smaller = &c1;
        bigger = &c2;
    } else {
        smaller = &c2;
        bigger = &c1;
    }

    cout << "--- Analiz ---" << endl;
    cout << "Menshiy kub: " << smaller->getName() << endl;

    double vSmall = smaller->calculateVolume();
    double vBig = bigger->calculateVolume();

    if (vSmall <= 0) {
        cout << "Vnimanie: U menshego kuba net vnutrennego ob'ema!" << endl;
    } else {
        double count = vBig / vSmall;
        cout << "Chtoby zapolnit' " << bigger->getName() << " (" << vBig << " cm^3),\n"
             << "nuzhno " << count << " kubov " << smaller->getName() << " (" << vSmall << " cm^3)." << endl;
    }

    return 0;
}