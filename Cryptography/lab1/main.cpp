#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ============================================================================
// // 2 ЗАДАНИЕ: Создание функций CSR_enc_math и CSR_dec_math
// // 3 ЗАДАНИЕ: Использование математической формулы шифрования/дешифрования
// ============================================================================

// Формула шифрования Цезаря: C = (P + k) mod 26
string CSR_enc_math(const string& text, int shift) {
    string result = "";
    int k = shift % 26;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += base + (c - base + k) % 26;
        } else {
            result += c;
        }
    }
    return result;
}

// Формула дешифрования Цезаря: P = (C - k + 26) mod 26
string CSR_dec_math(const string& text, int shift) {
    string result = "";
    int k = shift % 26;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += base + (c - base - k + 26) % 26;
        } else {
            result += c;
        }
    }
    return result;
}

string CSR_encrypt(const string& text, int shift) {
    return CSR_enc_math(text, shift);
}

string CSR_decrypt(const string& text, int shift) {
    return CSR_dec_math(text, shift);
}

// ============================================================================
// // 5 ЗАДАНИЕ: Создание тела функции CSK_encrypt (Шифр Виженера / Ключевое слово)
// ============================================================================

string CSK_encrypt(const string& text, const string& key) {
    string result = "";
    if (key.empty()) return text;

    size_t key_index = 0;
    size_t key_len = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base_text = isupper(c) ? 'A' : 'a';
            char key_char = key[key_index % key_len];
            int shift = toupper(key_char) - 'A';

            result += base_text + (c - base_text + shift) % 26;
            key_index++;
        } else {
            result += c;
        }
    }
    return result;
}

string CSK_decrypt(const string& text, const string& key) {
    string result = "";
    if (key.empty()) return text;

    size_t key_index = 0;
    size_t key_len = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base_text = isupper(c) ? 'A' : 'a';
            char key_char = key[key_index % key_len];
            int shift = toupper(key_char) - 'A';

            result += base_text + (c - base_text - shift + 26) % 26;
            key_index++;
        } else {
            result += c;
        }
    }
    return result;
}

// ============================================================================
// // 7 ЗАДАНИЕ: Создание тела функции CSK_keygen
// // 8 ЗАДАНИЕ: Алгоритм генерации ключевого потока (повторение ключа до длины текста)
// ============================================================================

string CSK_keygen(const string& text, const string& key) {
    if (key.empty()) return "";

    string keystream = "";
    size_t key_index = 0;
    size_t key_len = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            // Формируем поток ключа в верхнем регистре, ориентируясь на буквенные символы текста
            keystream += toupper(key[key_index % key_len]);
            key_index++;
        } else {
            keystream += c; // Пробелы и знаки пунктуации дублируем в ключевой поток без изменений
        }
    }
    return keystream;
}

// ============================================================================
// // 9 ЗАДАНИЕ: Создание тела функции VGN_encrypt (Шифрование Виженера)
// ============================================================================

string VGN_encrypt(const string& text, const string& key) {
    // Используем CSK_keygen для получения сгенерированного ключевого потока
    string keystream = CSK_keygen(text, key);
    string result = "";

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            char base_text = isupper(c) ? 'A' : 'a';
            int shift = keystream[i] - 'A';

            // Применяем математическую формулу Виженера: C_i = (P_i + K_i) mod 26
            result += base_text + (c - base_text + shift) % 26;
        } else {
            result += c;
        }
    }
    return result;
}

// ============================================================================
// ГЛАВНЫЙ БЛОК: Выполнение и проверка всех заданий (1-10)
// ============================================================================

int main() {
    // // 1 ЗАДАНИЕ
    cout << "====================================================" << endl;
    cout << "// 1 ЗАДАНИЕ: Проверка шифрования Цезаря" << endl;
    cout << "====================================================" << endl;

    string msg1 = "IWILLBEHEREONMONDAY";
    int shift1 = 7;
    string expected1 = "PDPSSILOLYLVUTVUKHF";
    string enc1 = CSR_enc_math(msg1, shift1);

    cout << "a) Сообщение: " << msg1 << endl;
    cout << "b) Шаг: " << shift1 << endl;
    cout << "c) Вычислено:  " << enc1 << endl;
    cout << "Результат: " << (enc1 == expected1 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО [ERR]") << endl << endl;

    // // 4 и 6 ЗАДАНИЯ
    cout << "====================================================" << endl;
    cout << "// 4 и 6 ЗАДАНИЯ: Проверка шифрования с ключом" << endl;
    cout << "====================================================" << endl;

    string msg2 = "IWILLBEHEREONMONDAY";
    string key2 = "MEETINGTIME";
    string expected2 = "CWCHHENBNQNLKJLKIMY";

    string enc2 = CSK_encrypt(msg2, key2);

    cout << "a) Сообщение: " << msg2 << endl;
    cout << "b) Ключ: " << key2 << endl;
    cout << "c) Вычислено:  " << enc2 << endl;
    cout << "Результат: " << (enc2 == expected2 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО (Ошибка в условии лабы) [ERR]") << endl << endl;

    // // 10 ЗАДАНИЕ: Проверка VGN_encrypt и генерации ключа CSK_keygen
    cout << "====================================================" << endl;
    cout << "// 10 ЗАДАНИЕ: Проверка функции VGN_encrypt" << endl;
    cout << "====================================================" << endl;

    string msg10 = "IWILLBEHEREONMONDAY";
    string key10 = "MTIME";
    string expected10 = "UPQXPNXPQVQHVYSZWIK";

    // 7-8 задания: Генерация ключевого потока
    string generated_keystream = CSK_keygen(msg10, key10);
    // 9 задание: Шифрование
    string enc10 = VGN_encrypt(msg10, key10);

    cout << "a) Сообщение для шифрования: " << msg10 << endl;
    cout << "b) Ключ: " << key10 << endl;
    cout << "   Сгенерированный поток ключа (CSK_keygen): " << generated_keystream << endl;
    cout << "c) Зашифрованное (из условия): " << expected10 << endl;
    cout << "   Зашифрованное (вычислено):  " << enc10 << endl;
    cout << "Результат проверки: " << (enc10 == expected10 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО [ERR]") << endl;
    cout << "====================================================" << endl;

    return 0;
}