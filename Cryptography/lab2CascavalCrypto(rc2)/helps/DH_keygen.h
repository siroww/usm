#pragma once

bool primenumtest(unsigned long long number);
unsigned long long randnumgen(unsigned long long minimum, unsigned long long maximum);
unsigned long long exponentiation(unsigned long long base, unsigned long long exponent, unsigned long long modulus);
unsigned long long DH_keygen();

/*
 Объявления функций демонстрации Диффи — Хеллмана: проверка простоты,
 выбор простого числа из диапазона, быстрое возведение в степень по модулю
 и получение общего секрета для использования в основной программе.
 */