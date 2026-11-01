#include <iostream>
#include <cstdlib>
#include <ctime>
#include "./helps/DH_keygen.h"
#include "./helps/RC2_E_D.h"

using namespace std;

int main() {
    srand(time(0));

    // 1. Генерируем общий ключ с помощью Диффи-Хеллмана
    unsigned long long key_num = DH_keygen();

    // Превращаем полученный секрет в массив байт для ключа RC2 (8 байт)
    unsigned char secret_key[8] = {0};
    for(int i = 0; i < 8; i++) {
        secret_key[i] = (key_num >> (i * 8)) & 0xFF;
    }

    unsigned short subkeys[64];
    rc2_key_expansion(secret_key, 8, 128, subkeys);

    // 2. Исходный блок открытого текста
    unsigned short block[4] = { 0x1111, 0x2222, 0x3333, 0x4444 };
    
    cout << "Исходный текст:   " << hex << block[0] << " " << block[1] << " " << block[2] << " " << block[3] << dec << "\n";

    // 3. Шифруем
    RC2_encrypt(block, subkeys);
    cout << "Шифротекст:       " << hex << block[0] << " " << block[1] << " " << block[2] << " " << block[3] << dec << "\n";

    // 4. Расшифровываем обратно
    RC2_decrypt(block, subkeys);
    cout << "Расшифрованный:   " << hex << block[0] << " " << block[1] << " " << block[2] << " " << block[3] << dec << "\n";

    return 0;
}

/*
 Точка входа в программу. Сначала генерируется общий секрет по протоколу
 Диффи — Хеллмана, затем его младшие 8 байт используются как ключ RC2.
 Программа формирует подключи, шифрует один 64-битный блок и сразу
 расшифровывает его, чтобы показать восстановление исходных данных.
 */