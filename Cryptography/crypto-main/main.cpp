#include <iostream>
#include <string>
#include <vector>

#include "include/globals.h"
#include "include/file.h"
#include "include/colorise.hpp"
#include "include/math_x.h"

#include "include/test_math.h"

const char LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
const char LETTERS2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char LETTERS3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

int main(int argc, char *argv[]) {
    if (argc < 2) {

        std::cout << echo(
            "* Copyright (C) 2026 Кашкавал Степан\n"
            "*\n"
            "* Эта программа распространяется свободно: вы можете использовать,\n"
            "* изменять и распространять её в соответствии с условиями GNU GPL.\n"
            "*\n"
            "* Программа предоставляется как есть, без гарантий,\n"
            "* включая их коммерческую пригодность и пригодность для конкретной цели.\n"
            "*\n"
            "* Вы должны были получить копию GNU General Public License\n"
            "* вместе с этой программой. Если нет, см. <https://www.gnu.org/licenses/>.\n"
            "\n"
            "\n"
            "\n"
            "Использование: " + std::string(argv[0]) + " <опция> <сообщение>\n"
             "Опции:\n"
             " -encrypt  Шифрование (Caesar Shift)\n"
             " -Ecsr     Шифрование (Caesar Shift, alias)\n"
             " -Dcsr  Расшифрование (Caesar Shift)\n"
             " -Ecsk  Шифрование (Caesar Keyword)\n"
             " -Dcsk  Расшифрование (Caesar Keyword)\n"
             " -Evgn  Шифрование (Vigenere)\n"
             " -Dvgn  Расшифрование (Vigenere)\n"
             " -GFm   Умножение в GF(2)\n"
             " -PEG   Полиномиальный расширенный алгоритм Евклида\n"
             " -Tlog  Таблица умножения GF(2)\n"
             " -F     Чтение файла\n"
             " -I     Интерактивный режим\n"
             " -v     Версия\n");
        exit(1);
    }

    std::string opt = argv[1];
    std::string msg_str = "";
    std::vector<char> msg_buffer;
    char *msg = nullptr;
    std::string alg = "";
    std::string file = "";

    // Обработка интерактивного режима (-I)
    if (opt == "-I") {
        if (argc > 2) {
            alg = argv[2];
        } else {
            std::cerr << echo((std::string)argv[0] + ": missing algorithm argument for -I\n");
            exit(2);
        }
    }
    // Обработка режима файлов (-F)
    else if (opt == "-t" || opt == "-T") {
        START_TEST();
        exit(0);
    } else if (opt == "-F") {
        if (argc > 3) {
            alg = argv[2];
            file = argv[3];
        } else {
            std::cerr << echo((std::string)argv[0] + ": missing algorithm or file argument for -F\n");
            exit(2);
        }
    }
    // Обычный режим с сообщением
    else {
        if (opt == "-v") {
            std::cout << "v1.0.0\n";
            exit(0);
        }
        if (argc < 3) {
            if (opt[0] == '-') {
                std::cerr << echo((std::string)argv[0] + ": missing message argument\n");
                exit(2);
            } else {
                std::cerr << echo((std::string)argv[0] + ": missing option argument\n");
                exit(2);
            }
        }
        msg_str = argv[2];
        msg_buffer.assign(msg_str.begin(), msg_str.end());
        msg_buffer.push_back('\0');
        msg = msg_buffer.data();
    }


    if (opt == "-encrypt" || opt == "-Ecsr") {
        CSR_encrypt(msg);
    } else if (opt == "-Dcsr") {
        CSR_decrypt(msg);
    } else if (opt == "-Dcsrm") {
        CSR_dec_math(msg);
    } else if (opt == "-Ecsm") {
        CSR_enc_math(msg);
    } else if (opt == "-Ecsk") {
        encrypt_caesar_keyword(msg);
    } else if (opt == "-Dcsk") {
        decrypt_caesar_keyword(msg);
    } else if (opt == "-Evgn") {
        VGN_encript(msg);
    } else if (opt == "-Dvgn") {
        VGN_decript(msg);
    } else if (opt == "-Evgns") {
        VGN_enc_seed(msg);
    } else if (opt == "-GFm") {
        if (argc < 4) {
            std::cerr << echo((std::string)argv[0] + ": missing arguments for -GFm\n");
            exit(2);
        }
        uint8_t a = static_cast<uint8_t>(std::stoi(argv[2]));
        uint8_t b = static_cast<uint8_t>(std::stoi(argv[3]));
        std::cout << static_cast<int>(gf_mult(a, b)) << '\n';
        exit(0);
    } else if (opt == "-PEG") {
        if (argc < 3) {
            std::cerr << echo((std::string)argv[0] + ": missing argument for -PEG\n");
            exit(2);
        }
        uint16_t value = static_cast<uint16_t>(std::stoi(argv[2]));
        uint8_t* res = poly_ext_gcd(value, 0x11B);
        std::cout << "gcd=" << static_cast<int>(res[0])
                  << " inverse=" << static_cast<int>(res[1]) << '\n';
        exit(0);
    } else if (opt == "-Tlog") {
        if (argc < 4) {
            std::cerr << echo((std::string)argv[0] + ": missing arguments for -Tlog\n");
            exit(2);
        }
        uint8_t a = static_cast<uint8_t>(std::stoi(argv[2]));
        uint8_t b = static_cast<uint8_t>(std::stoi(argv[3]));
        std::cout << static_cast<int>(gf_mult_table(a, b)) << '\n';
        exit(0);
    } else if (opt == "-I") {
        if (alg == "Idh") {
            DIFFI_HELLMAN();
        } else {
            std::cerr << echo((std::string)argv[0] + ": unknown interactive algorithm '" + alg + "'\n");
            exit(3);
        }
    } else if (opt == "-F") {

        std::string file_content = fileRead(file);
        std::vector<char> file_buffer(file_content.begin(), file_content.end());
        file_buffer.push_back('\0');

        if (alg == "Ecsr") {
            CSR_encrypt(file_buffer.data());
        } else if (alg == "Dcsr") {
            CSR_decrypt(file_buffer.data());
        } else if (alg == "Ecsk") {
            encrypt_caesar_keyword(file_buffer.data());
        } else if (alg == "Dcsk") {
            decrypt_caesar_keyword(file_buffer.data());
        } else if (alg == "Evgn") {
            VGN_encript(file_buffer.data());
        } else if (alg == "Dvgn") {
            VGN_decript(file_buffer.data());
        } else {
            std::cerr << echo((std::string)argv[0] + ": unknown algorithm '" + alg + "'\n");
            exit(3);
        }

    } else {
        std::cerr << echo((std::string)argv[0] + ": unknown option '" + opt + "'\n");
        exit(3);
    }

    return 0;
}
