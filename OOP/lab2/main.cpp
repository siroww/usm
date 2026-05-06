#include <iostream>
#include <clocale>

// Прототип функции для сравнения кубов.
void compareCubes();

using namespace std;

int main() {
    system("chcp 1251 > nul");
    int choice = 0;

    do {
        cout << "--- Меню сравнения кубов ---\n";
        cout << "1. Сравнить два куба\n";
        cout << "2. Выход\n";
        cout << "Выберите пункт: ";
        cin >> choice;

        switch (choice) {
            case 1:
                compareCubes();
                break;
            case 2:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный вариант. Повторите ввод.\n";
                break;
        }

        cout << endl;
    } while (choice != 2);

    return 0;
}

