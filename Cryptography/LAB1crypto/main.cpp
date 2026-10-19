
// ./program -encrypt "HELLO WORLD"
// ./program -Dcsr "KHOOR ZRUOG"
// ./program -Ecsr "HELLO WORLD"
// ./program -Ecsk "hello world"
// ./program -Dcsk "btggj vjmgp"
// ./program -Evgn "HELLOWORLD123"
// ./program -Dvgn "RIjVSuYVjN5PC"
// ./program -Ecsm "HELLO WORLD"
// ./program -Dcsrm "KHOOR ZRUOG"
// ./program -Evgns "HELLOWORLD123"



#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "include/file.h"
#include "include/globals.h"
#include "include/math_x.h"
#include "include/test_math.h"

const char LETTERS[] = "abcdefghijklmnopqrstuvwxyz";
const char LETTERS2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const char LETTERS3[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr
            << "Usage: " << argv[0] << " <option> <message>\n"
            << "Options:\n"
            << " -encrypt  Encrypt with Caesar shift\n"
            << " -Ecsr     Encrypt with Caesar shift\n"
            << " -Dcsr     Decrypt with Caesar shift\n"
            << " -Ecsk     Encrypt with Caesar keyword\n"
            << " -Dcsk     Decrypt with Caesar keyword\n"
            << " -Evgn     Encrypt with Vigenere\n"
            << " -Dvgn     Decrypt with Vigenere\n"
            << " -GFm      Multiply in GF(2^8)\n"
            << " -PEG      Find a polynomial inverse\n"
            << " -Tlog     Multiply using GF tables\n"
            << " -F        Read input from a file\n"
            << " -I        Run interactive mode\n"
            << " -v        Show version\n";
        return 1;
    }

    const std::string option = argv[1];
    std::string algorithm;
    std::string file_path;
    std::string message_text;
    std::vector<char> message_buffer;
    char *message = nullptr;

    if (option == "-I") {
        if (argc <= 2) {
            std::cerr << argv[0] << ": missing algorithm for -I\n";
            return 2;
        }
        algorithm = argv[2];
    } else if (option == "-t" || option == "-T") {
        return START_TEST();
    } else if (option == "-F") {
        if (argc <= 3) {
            std::cerr << argv[0] << ": missing algorithm or file for -F\n";
            return 2;
        }
        algorithm = argv[2];
        file_path = argv[3];
    } else if (option == "-v") {
        std::cout << "v1.0.0\n";
        return 0;
    } else {
        if (argc < 3) {
            std::cerr << argv[0] << ": missing message\n";
            return 2;
        }
        message_text = argv[2];
        message_buffer.assign(message_text.begin(), message_text.end());
        message_buffer.push_back('\0');
        message = message_buffer.data();
    }

    if (option == "-encrypt" || option == "-Ecsr") {
        CSR_encrypt(message);
    } else if (option == "-Dcsr") {
        CSR_decrypt(message);
    } else if (option == "-Dcsrm") {
        CSR_dec_math(message);
    } else if (option == "-Ecsm") {
        CSR_enc_math(message);
    } else if (option == "-Ecsk") {
        encrypt_caesar_keyword(message);
    } else if (option == "-Dcsk") {
        decrypt_caesar_keyword(message);
    } else if (option == "-Evgn") {
        VGN_encript(message);
    } else if (option == "-Dvgn") {
        VGN_decript(message);
    } else if (option == "-Evgns") {
        VGN_enc_seed(message);
    } else if (option == "-GFm") {
        if (argc < 4) {
            std::cerr << argv[0] << ": missing arguments for -GFm\n";
            return 2;
        }
        const uint8_t first = static_cast<uint8_t>(std::stoi(argv[2]));
        const uint8_t second = static_cast<uint8_t>(std::stoi(argv[3]));
        std::cout << static_cast<int>(gf_mult(first, second)) << '\n';
    } else if (option == "-PEG") {
        const uint16_t value = static_cast<uint16_t>(std::stoi(argv[2]));
        uint8_t *result = poly_ext_gcd(value, 0x11B);
        std::cout << "gcd=" << static_cast<int>(result[0])
                  << " inverse=" << static_cast<int>(result[1]) << '\n';
    } else if (option == "-Tlog") {
        if (argc < 4) {
            std::cerr << argv[0] << ": missing arguments for -Tlog\n";
            return 2;
        }
        const uint8_t first = static_cast<uint8_t>(std::stoi(argv[2]));
        const uint8_t second = static_cast<uint8_t>(std::stoi(argv[3]));
        precompute_tables(0x03);
        gf_mult_table(first, second);
        std::cout << '\n';
    } else if (option == "-I") {
        if (algorithm != "Idh") {
            std::cerr << argv[0] << ": unknown interactive algorithm '"
                      << algorithm << "'\n";
            return 3;
        }
        DIFFI_HELLMAN();
    } else if (option == "-F") {
        const std::string file_content = fileRead(file_path);
        std::vector<char> file_buffer(file_content.begin(), file_content.end());
        file_buffer.push_back('\0');
        char *file_message = file_buffer.data();

        if (algorithm == "Ecsr") {
            CSR_encrypt(file_message);
        } else if (algorithm == "Dcsr") {
            CSR_decrypt(file_message);
        } else if (algorithm == "Ecsk") {
            encrypt_caesar_keyword(file_message);
        } else if (algorithm == "Dcsk") {
            decrypt_caesar_keyword(file_message);
        } else if (algorithm == "Evgn") {
            VGN_encript(file_message);
        } else if (algorithm == "Dvgn") {
            VGN_decript(file_message);
        } else {
            std::cerr << argv[0] << ": unknown algorithm '" << algorithm << "'\n";
            return 3;
        }
    } else {
        std::cerr << argv[0] << ": unknown option '" << option << "'\n";
        return 3;
    }

    return 0;
}
