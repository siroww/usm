#!/bin/sh
set -eu

cd "$(dirname "$0")"

show_result()
{
    label=$1
    shift
    explanation=$1
    shift
    printf '\n== %s ==\n%s\n' "$label" "$explanation"
    "$@"
}

run_with_input()
{
    input=$1
    shift
    printf '%s\n' "$input" | "$@" | sed \
        -e 's/Enter key: //g' \
        -e 's/Enter private key a: //g' \
        -e 's/Enter private key b: //g' \
        -e 's/Input a : //g' \
        -e 's/Input b : //g' \
        -e 's/Input p : //g'
}

plain="HELLO WORLD"
caesar_cipher=$(run_with_input 3 ./program -encrypt "$plain")
show_result "Шифр Цезаря (-encrypt)" "Шифруем «${plain}» сдвигом на 3 буквы. Ниже появится шифротекст." printf '%s\n' "$caesar_cipher"
show_result "Расшифровка Цезаря (-Dcsr)" "Расшифровываем предыдущий результат тем же ключом 3. Должно получиться исходное сообщение." run_with_input 3 ./program -Dcsr "$caesar_cipher"

keyword_plain="hello world"
keyword_cipher=$(run_with_input crypto ./program -Ecsk "$keyword_plain")
show_result "Цезарь с ключевым словом (-Ecsk)" "Шифруем «${keyword_plain}», строя алфавит по ключевому слову crypto." printf '%s\n' "$keyword_cipher"
show_result "Расшифровка Цезаря с ключом (-Dcsk)" "Расшифровываем шифротекст тем же ключом crypto. Ожидаемый результат: исходный текст." run_with_input crypto ./program -Dcsk "$keyword_cipher"

vigenere_plain="HELLOWORLD123"
vigenere_cipher=$(run_with_input KEY ./program -Evgn "$vigenere_plain")
show_result "Шифр Виженера (-Evgn)" "Шифруем «${vigenere_plain}» повторяющимся ключом KEY." printf '%s\n' "$vigenere_cipher"
show_result "Расшифровка Виженера (-Dvgn)" "Расшифровываем результат тем же ключом KEY. Должно восстановиться исходное сообщение." run_with_input KEY ./program -Dvgn "$vigenere_cipher"

show_result "Умножение в GF(2^8) (-GFm)" "Умножаем числа 87 и 131 в конечном поле GF(2^8). Результат выводится десятичным числом." ./program -GFm 87 131
show_result "Обратный элемент многочлена (-PEG)" "Находим обратный элемент для 87 в поле AES GF(2^8). gcd=1 означает, что обратный элемент существует." ./program -PEG 87
show_result "Умножение по таблицам GF (-Tlog)" "Считаем произведение 87 и 131 в GF(2^8), используя предварительно построенные таблицы логарифмов." ./program -Tlog 87 131

temp_input=$(mktemp "${TMPDIR:-/tmp}/crypto-demo-input.XXXXXX")
temp_cipher=$(mktemp "${TMPDIR:-/tmp}/crypto-demo-cipher.XXXXXX")
trap 'rm -f "$temp_input" "$temp_cipher"' EXIT HUP INT TERM
printf '%s\n' "FILE MODE" > "$temp_input"
file_cipher=$(run_with_input 3 ./program -F Ecsr "$temp_input")
show_result "Шифрование файла (-F Ecsr)" "Читаем временный файл со строкой FILE MODE и шифруем его сдвигом 3. Ниже показан результат." printf '%s\n' "$file_cipher"
printf '%s\n' "$file_cipher" > "$temp_cipher"
show_result "Расшифровка файла (-F Dcsr)" "Расшифровываем файл с шифротекстом тем же ключом. Должна вернуться строка FILE MODE." run_with_input 3 ./program -F Dcsr "$temp_cipher"

show_result "Обмен ключами Диффи—Хеллмана (-I Idh)" "Запускаем демонстрацию с закрытыми показателями 5 и 7. В конце обе стороны должны получить одинаковый общий ключ." run_with_input "5
7" ./program -I Idh

show_result "Виженер с seed (-Evgns)" "Шифруем сообщение ключом KEY с фиксированным seed. Эта демонстрационная функция показывает только шифрование." run_with_input KEY ./program -Evgns "$vigenere_plain"
show_result "Тесты математических алгоритмов (-t)" "Запускаем проверки GF(2^8), возведения в степень, обратного элемента и дискретных логарифмов. Сравните вычисленные значения с ожидаемыми; в конце тесты должны пройти." ./program -t
