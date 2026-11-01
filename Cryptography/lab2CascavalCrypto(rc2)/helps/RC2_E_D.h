#pragma once
#include <vector>
#include <string>

extern const unsigned char pitable[256];

unsigned short ROL(unsigned short value, int count);
unsigned short ROR(unsigned short value, int count);
void rc2_key_expansion(const unsigned char* key_bytes, int key_len_bytes, int t1, unsigned short L[64]);
void mixing_round(unsigned short& R0, unsigned short& R1, unsigned short& R2, unsigned short& R3, const unsigned short subkeys[64], int& j);
void mashing_round(unsigned short& R0, unsigned short& R1, unsigned short& R2, unsigned short& R3, const unsigned short subkeys[64]);
void RC2_encrypt(unsigned short block[4], const unsigned short subkeys[64]);
void RC2_decrypt(unsigned short block[4], const unsigned short subkeys[64]);
std::vector<unsigned char> rc2_padding(const std::string& input);

/*
 Объявления таблицы и функций RC2: операции циклического сдвига, подготовка
 подключей, раунды шифрования/дешифрования и дополнение данных до размера
 блока. Реализации находятся в components/RC2_E_D.cpp.
 */