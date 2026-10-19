#include <stdio.h>
#include <string.h>
#include "../include/globals.h"

static char *build_keyword_alphabet(void)
{
    static char alphabet[128];
    printf("Enter key: ");
    if (scanf("%99s", alphabet) != 1) return NULL;

    strcat(alphabet, LETTERS);
    size_t alphabet_length = strlen(alphabet);

    for (size_t index = 0; index < alphabet_length; index++) {
        for (size_t next = index + 1; next < alphabet_length; next++) {
            if (alphabet[index] == alphabet[next]) {
                for (size_t move = next; move + 1 < alphabet_length; move++) {
                    alphabet[move] = alphabet[move + 1];
                }
                alphabet_length--;
                next--;
            }
        }
    }

    alphabet[alphabet_length] = '\0';
    return alphabet;
}

void encrypt_caesar_keyword(char *message)
{
    char *alphabet = build_keyword_alphabet();
    if (!alphabet) return;

    const size_t letter_count = strlen(LETTERS);
    const size_t message_length = strlen(message);
    for (size_t index = 0; index < message_length; index++) {
        for (size_t letter_index = 0; letter_index < letter_count; letter_index++) {
            if (message[index] == LETTERS[letter_index]) {
                message[index] = alphabet[letter_index];
                break;
            }
        }
    }
    printf("%s\n", message);
}

void decrypt_caesar_keyword(char *message)
{
    char *alphabet = build_keyword_alphabet();
    if (!alphabet) return;

    const size_t message_length = strlen(message);
    const size_t alphabet_length = strlen(alphabet);
    for (size_t index = 0; index < message_length; index++) {
        for (size_t letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == alphabet[letter_index]) {
                message[index] = LETTERS[letter_index];
                break;
            }
        }
    }
    printf("%s\n", message);
}
