#include <iostream>
#include <cstdlib>
#include "../helps/DH_keygen.h"

using namespace std;

// Проверка числа на простоту
bool primenumtest(unsigned long long number) {
    if (number <= 1) return false;
    for (unsigned long long i = 2; i * i <= number; ++i) {
        if (number % i == 0) return false;
    }
    return true;
}

// Генерация случайного простого числа
unsigned long long randnumgen(unsigned long long minimum, unsigned long long maximum) {
    unsigned long long candidate;
    do {
        candidate = minimum + rand() % (maximum - minimum + 1);
    } while (!primenumtest(candidate));
    return candidate;
}

// Быстрое возведение в степень по модулю
unsigned long long exponentiation(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Функция генерации ключей Диффи-Хеллмана
// Измените тип с void на unsigned long long
unsigned long long DH_keygen() {
    unsigned long long p = randnumgen(10, 100);
    unsigned long long g = randnumgen(2, 10);
    unsigned long long n = randnumgen(1, 50); 
    unsigned long long m = randnumgen(1, 50); 

    cout << "=== Протокол Диффи-Хеллмана ===" << "\n";
    cout << "Модуль p = " << p << ", Генератор g = " << g << "\n";

    unsigned long long z1 = exponentiation(g, n, p);
    unsigned long long z2 = exponentiation(g, m, p);

    unsigned long long shared_secret_1 = exponentiation(z2, n, p);

    cout << "Общий секрет вычислен успешно: " << shared_secret_1 << "\n\n";
    
    return shared_secret_1; // Возвращаем ключ для RC2!
}

/*
 Реализация демонстрации Диффи — Хеллмана: выбирает простые числа и
 секретные показатели, вычисляет открытые значения и общий секрет с
 помощью быстрого возведения в степень по модулю. Здесь используются
 rand() и малые числа, поэтому реализация предназначена только для
 учебного примера и не обеспечивает криптографическую защиту.
 */