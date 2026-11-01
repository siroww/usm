#include "../helps/RC2_E_D.h"
#include "../helps/pitable.h"

#include <stdexcept>

// Таблица подстановок (Pi-таблица) по стандарту RFC 2268


unsigned short ROL(unsigned short value, int count) {
    count %= 16;
    if (count == 0) return value;
    return (value << count) | (value >> (16 - count));
}

unsigned short ROR(unsigned short value, int count) {
    count %= 16;
    if (count == 0) return value;
    return (value >> count) | (value << (16 - count));
}

// Расширение ключа (Key Expansion)
void rc2_key_expansion(const unsigned char* key_bytes, int key_len_bytes, int t1, unsigned short L[64]) {
    if (key_bytes == nullptr || L == nullptr || key_len_bytes < 1 || key_len_bytes > 128 ||
        t1 < 1 || t1 > 1024) {
        throw std::invalid_argument("Некорректная длина ключа или эффективная длина RC2");
    }

    unsigned char L_bytes[128];
    for (int i = 0; i < key_len_bytes; i++) {
        L_bytes[i] = key_bytes[i];
    }
    for (int i = key_len_bytes; i < 128; i++) {
        L_bytes[i] = pitable[(L_bytes[i - 1] + L_bytes[i - key_len_bytes]) & 0xFF];
    }
    const int t8 = (t1 + 7) / 8;
    const unsigned char tm = static_cast<unsigned char>(0xFF >> (8 * t8 - t1));
    L_bytes[128 - t8] = pitable[L_bytes[128 - t8] & tm];
    for (int i = 127 - t8; i >= 0; i--) {
        L_bytes[i] = pitable[L_bytes[i + 1] ^ L_bytes[i + t8]];
    }
    for (int i = 0; i < 64; i++) {
        L[i] = (unsigned short)(L_bytes[2 * i]) | ((unsigned short)(L_bytes[2 * i + 1]) << 8);
    }
}

// Перемешивание (Mixing)
void mixing_round(unsigned short& R0, unsigned short& R1, unsigned short& R2, unsigned short& R3, const unsigned short subkeys[64], int& j) {
    R0 = R0 + subkeys[j++] + (R3 & R2) + (static_cast<unsigned short>(~R3) & R1);
    R0 = ROL(R0, 1);
    R1 = R1 + subkeys[j++] + (R0 & R3) + (static_cast<unsigned short>(~R0) & R2);
    R1 = ROL(R1, 2);
    R2 = R2 + subkeys[j++] + (R1 & R0) + (static_cast<unsigned short>(~R1) & R3);
    R2 = ROL(R2, 3);
    R3 = R3 + subkeys[j++] + (R2 & R1) + (static_cast<unsigned short>(~R2) & R0);
    R3 = ROL(R3, 5);
}

// Наложение (Mashing)
void mashing_round(unsigned short& R0, unsigned short& R1, unsigned short& R2, unsigned short& R3, const unsigned short subkeys[64]) {
    R0 = R0 + subkeys[R3 & 63];
    R1 = R1 + subkeys[R0 & 63];
    R2 = R2 + subkeys[R1 & 63];
    R3 = R3 + subkeys[R2 & 63];
}

// Шифрование блока
void RC2_encrypt(unsigned short block[4], const unsigned short subkeys[64]) {
    unsigned short R0 = block[0];
    unsigned short R1 = block[1];
    unsigned short R2 = block[2];
    unsigned short R3 = block[3];

    int j = 0;
    for (int i = 0; i < 16; i++) {
        mixing_round(R0, R1, R2, R3, subkeys, j);
        if (i == 4 || i == 10) {
            mashing_round(R0, R1, R2, R3, subkeys);
        }
    }

    block[0] = R0;
    block[1] = R1;
    block[2] = R2;
    block[3] = R3;
}

// Дешифрование блока (строго обратная операция в правильном порядке)
void RC2_decrypt(unsigned short block[4], const unsigned short subkeys[64]) {
    unsigned short R0 = block[0];
    unsigned short R1 = block[1];
    unsigned short R2 = block[2];
    unsigned short R3 = block[3];

    int j = 64; // Идем по подключам с конца
    for (int i = 15; i >= 0; i--) {
        
        // 1. Сначала на раундах 11 и 4 отменяем мэш-раунд (наложение) ДО микса
        if (i == 10 || i == 4) {
            R3 = R3 - subkeys[R2 & 63];
            R2 = R2 - subkeys[R1 & 63];
            R1 = R1 - subkeys[R0 & 63];
            R0 = R0 - subkeys[R3 & 63];
        }

        // 2. Затем отменяем обратный микс-шаг (вычитание и ROR)
        R3 = ROR(R3, 5);
        R3 = R3 - subkeys[--j] - (R2 & R1) -
             (static_cast<unsigned short>(~R2) & R0);

        R2 = ROR(R2, 3);
        R2 = R2 - subkeys[--j] - (R1 & R0) -
             (static_cast<unsigned short>(~R1) & R3);

        R1 = ROR(R1, 2);
        R1 = R1 - subkeys[--j] - (R0 & R3) -
             (static_cast<unsigned short>(~R0) & R2);

        R0 = ROR(R0, 1);
        R0 = R0 - subkeys[--j] - (R3 & R2) -
             (static_cast<unsigned short>(~R3) & R1);
    }

    block[0] = R0;
    block[1] = R1;
    block[2] = R2;
    block[3] = R3;
}
// Дополнение (Padding)
std::vector<unsigned char> rc2_padding(const std::string& input) {
    std::vector<unsigned char> data(input.begin(), input.end());
    size_t padding_len = 8 - (data.size() % 8);
    for (size_t i = 0; i < padding_len; i++) {
        data.push_back((unsigned char)padding_len);
    }
    return data;
}

/*
 Реализация вспомогательных операций, расширения ключа и шифра RC2 для
 одного 64-битного блока: блок обрабатывается 16 раундами смешивания,
 а на раундах 4 и 11 дополнительно применяется наложение подключей.
 Расшифрование отменяет эти шаги в обратном порядке. Функция дополнения
 добавляет к данным от 1 до 8 байт, чтобы длина стала кратна размеру блока.
 */