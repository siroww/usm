#include <iostream>
#include <iomanip>
#include "Header/Cube.h"

using namespace std;

// Вывод подробных характеристик куба.
static void printCubeInfo(const Cube &cube, const char *label) {
    cout << fixed << setprecision(2);
    cout << label << " характеристики:\n";
    cout << "  Длина стороны: " << cube.getSide() << "\n";
    cout << "  Толщина стенок: " << cube.getThickness() << "\n";
    cout << "  Внутренняя сторона: " << cube.innerSide() << "\n";
    cout << "  Объем воды: " << cube.volume() << "\n";
}

// Сравнение двух кубов и расчет требуемого объема воды.
void compareCubes() {
    double side1, thickness1;
    double side2, thickness2;

    cout << "Введите длину стороны первого куба: ";
    cin >> side1;
    cout << "Введите толщину стенок первого куба: ";
    cin >> thickness1;

    cout << "Введите длину стороны второго куба: ";
    cin >> side2;
    cout << "Введите толщину стенок второго куба: ";
    cin >> thickness2;

    Cube cube1(side1, thickness1);
    Cube cube2(side2, thickness2);

    printCubeInfo(cube1, "Первый куб");
    printCubeInfo(cube2, "Второй куб");

    const Cube *smaller = &cube1;
    const Cube *larger = &cube2;

    if (cube2.volume() < cube1.volume()) {
        smaller = &cube2;
        larger = &cube1;
    }

    cout << "\nМеньший куб: " << (smaller == &cube1 ? "первый" : "второй") << ".\n";
    cout << "Чтобы заполнить больший куб водой, нужно "
         << fixed << setprecision(2)
         << (larger->volume() - smaller->volume()) << " единиц воды.\n";
}
