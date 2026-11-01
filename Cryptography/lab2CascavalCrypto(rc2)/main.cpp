#include <iostream>
#include <stdexcept>
#include "./helps/EllipticCurveDemo.h"
#include "./helps/RC2_E_D.h"

using namespace std;

int main() {
    // 1. Создаем ключи Алисы и Боба на кривой P-256.
    Point G = generator_point();
    vector<unsigned char> alice_secret = generate_private_key();
    vector<unsigned char> bob_secret = generate_private_key();
    Point A = scalar_mult(alice_secret, G);
    Point B = scalar_mult(bob_secret, G);

    vector<unsigned char> shared_secret_alice = derive_shared_secret(alice_secret, B);
    vector<unsigned char> shared_secret_bob = derive_shared_secret(bob_secret, A);
    if (shared_secret_alice != shared_secret_bob) {
        throw runtime_error("Стороны получили разные общие секреты ECDH");
    }
    vector<unsigned char> secret_key = derive_rc2_key(shared_secret_alice);

    unsigned short subkeys[64];
    rc2_key_expansion(secret_key.data(), static_cast<int>(secret_key.size()), 128, subkeys);

    cout << "=== Обмен ключами ECDH (P-256) ===\n";
    print_point("Генератор G", G);
    print_point("Открытый ключ Алисы", A);
    print_point("Открытый ключ Боба", B);
    cout << "Общий секрет ECDH получен обеими сторонами; ключ RC2: "
         << secret_key.size() << " байт\n\n";

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
 Точка входа в программу. Алиса и Боб получают общий секрет по ECDH
 на кривой P-256. Из него формируется ключ RC2, которым шифруется блок
 и затем проверяется восстановление исходных данных.
 */