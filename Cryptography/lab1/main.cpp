#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// ============================================================================
// БЛОК 1: ШИФР ЦЕЗАРЯ С ИСПОЛЬЗОВАНИЕМ МАТЕМАТИЧЕСКИХ ФОРМУЛ (Задания 2-3)
// ============================================================================

// Функция математического шифрования Цезаря: C = (P + k) mod 26
string CSR_enc_math(const string& text, int shift) {
    string result = "";
    int k = shift % 26; // Ограничиваем сдвиг пределами алфавита (0-25)

    for (char c : text) {
        if (isalpha(c)) { // Проверяем, является ли символ буквой
            // Определяем базовый символ: 'A' для заглавных, 'a' для строчных
            char base = isupper(c) ? 'A' : 'a';
            // Сдвигаем букву, берем остаток от деления на 26 и добавляем к базе
            result += base + (c - base + k) % 26;
        } else {
            result += c; // Знаки препинания и пробелы оставляем без изменений
        }
    }
    return result;
}

// Функция математического дешифрования Цезаря: P = (C - k + 26) mod 26
string CSR_dec_math(const string& text, int shift) {
    string result = "";
    int k = shift % 26;

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            // Вычитаем сдвиг, прибавляем 26 (чтобы не было отрицательных чисел) и берем % 26
            result += base + (c - base - k + 26) % 26;
        } else {
            result += c;
        }
    }
    return result;
}

// Общие обертки для вызова математических функций Цезаря
string CSR_encrypt(const string& text, int shift) {
    return CSR_enc_math(text, shift);
}

string CSR_decrypt(const string& text, int shift) {
    return CSR_dec_math(text, shift);
}

// ============================================================================
// БЛОК 2: ШИФР С КЛЮЧЕВЫМ СЛОВОМ / ВИЖЕНЕР (Задание 5)
// ============================================================================

// Функция шифрования с использованием ключевого слова
string CSK_encrypt(const string& text, const string& key) {
    string result = "";
    if (key.empty()) return text; // Если ключ пустой, возвращаем текст как есть

    size_t key_index = 0;
    size_t key_len = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            char base_text = isupper(c) ? 'A' : 'a';
            // Берем текущую букву ключа по кругу (с помощью оператора %)
            char key_char = key[key_index % key_len];
            int shift = toupper(key_char) - 'A'; // Вычисляем числовой сдвиг из буквы ключа

            // Шифруем символ по аналогии с Цезарем, но со сдвигом из ключа
            result += base_text + (c - base_text + shift) % 26;
            key_index++; // Переходим к следующей букве ключа только для букв текста
        } else {
            result += c;
        }
    }
    return result;
}

// Функция расшифрования с использованием ключевого слова
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

            // Обратная операция (дешифрование) с учетом добавления 26
            result += base_text + (c - base_text - shift + 26) % 26;
            key_index++;
        } else {
            result += c;
        }
    }
    return result;
}

// ============================================================================
// БЛОК 3: ГЕНЕРАЦИЯ КЛЮЧЕВОГО ПОТОКА (Задания 7-8)
// ============================================================================

// Функция генерации ключевого потока (keystream), повторяющего ключ под длину текста
string CSK_keygen(const string& text, const string& key) {
    if (key.empty()) return "";

    string keystream = "";
    size_t key_index = 0;
    size_t key_len = key.length();

    for (char c : text) {
        if (isalpha(c)) {
            // Достаем букву ключа по кругу и переводим в верхний регистр
            keystream += toupper(key[key_index % key_len]);
            key_index++;
        } else {
            keystream += c; // Пробелы и спецсимволы дублируются в потоке ключа
        }
    }
    return keystream;
}

// ============================================================================
// БЛОК 4: ШИФР ВИЖЕНЕРА (Задание 9)
// ============================================================================

// Функция шифрования Виженера с использованием сгенерированного потока ключа
string VGN_encrypt(const string& text, const string& key) {
    // Сначала генерируем полноценный поток ключа под длину текста
    string keystream = CSK_keygen(text, key);
    string result = "";

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            char base_text = isupper(c) ? 'A' : 'a';
            int shift = keystream[i] - 'A'; // Сдвиг берется из символа keystream

            // Математическая формула Виженера: C_i = (P_i + K_i) mod 26
            result += base_text + (c - base_text + shift) % 26;
        } else {
            result += c;
        }
    }
    return result;
}

// ============================================================================
// ГЛАВНЫЙ БЛОК (MAIN): Проверка работоспособности всех алгоритмов
// ============================================================================

int main() {
    // ТЕСТ 1: Проверка математического шифра Цезаря
    cout << "====================================================" << endl;
    cout << "// 1 ЗАДАНИЕ: Проверка шифрования Цезаря" << endl;
    cout << "====================================================" << endl;

    string msg1 = "IWILLBEHEREONMONDAY";
    int shift1 = 7;
    string expected1 = "PDPSSILOLYLVUTVUKHF";
    string enc1 = CSR_enc_math(msg1, shift1); // Вызываем шифрование со сдвигом 7

    cout << "a) Сообщение: " << msg1 << endl;
    cout << "b) Шаг: " << shift1 << endl;
    cout << "c) Вычислено:  " << enc1 << endl;
    // Сравниваем полученный результат с эталоном из методички
    cout << "Результат: " << (enc1 == expected1 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО [ERR]") << endl << endl;

    // ТЕСТ 2: Проверка шифрования с ключевым словом
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
    cout << "Результат: " << (enc2 == expected2 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО [ERR]") << endl << endl;

    // ТЕСТ 3: Проверка генерации ключа и шифра Виженера (Задания 7-10)
    cout << "====================================================" << endl;
    cout << "// 10 ЗАДАНИЕ: Проверка функции VGN_encrypt" << endl;
    cout << "====================================================" << endl;

    string msg10 = "IWILLBEHEREONMONDAY";
    string key10 = "MTIME";
    string expected10 = "UPQXPNXPQVQHVYSZWIK";

    // Генерация потока ключа
    string generated_keystream = CSK_keygen(msg10, key10);
    // Шифрование Виженера
    string enc10 = VGN_encrypt(msg10, key10);

    cout << "a) Сообщение для шифрования: " << msg10 << endl;
    cout << "b) Ключ: " << key10 << endl;
    cout << "   Сгенерированный поток ключа (CSK_keygen): " << generated_keystream << endl;
    cout << "c) Зашифрованное (из условия): " << expected10 << endl;
    cout << "   Зашифрованное (вычислено):  " << enc10 << endl;
    cout << "Результат проверки: " << (enc10 == expected10 ? "КОРРЕКТНО [OK]" : "НЕКОРРЕКТНО [ERR]") << endl;
    cout << "====================================================" << endl;

    return 0; // Завершение программы
}