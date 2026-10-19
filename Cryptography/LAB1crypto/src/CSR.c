#include <stdio.h>
#include <string.h>
#include "../include/globals.h"

static int read_shift(int *shift)
{
    printf("Enter key: ");
    if (scanf("%d", shift) != 1 || *shift < 0 || *shift > 25) {
        fprintf(stderr, "Invalid key: enter an integer from 0 to 25.\n");
        return 0;
    }
    return 1;
}

void CSR_decrypt(char *message)
{
    int shift;
    if (!read_shift(&shift)) return;

    const int alphabet_length = strlen(LETTERS2);
    shift = (shift % alphabet_length + alphabet_length) % alphabet_length;

    size_t message_length = strlen(message);
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS2[letter_index]) {
                message[index] = LETTERS2[(letter_index - shift + alphabet_length) % alphabet_length];
                break;
            }
        }
    }
    printf("%s\n", message);
}

void CSR_encrypt(char *message)
{
    int shift;
    if (!read_shift(&shift)) return;

    const int alphabet_length = strlen(LETTERS2);
    shift = (shift % alphabet_length + alphabet_length) % alphabet_length;

    size_t message_length = strlen(message);
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS2[letter_index]) {
                message[index] = LETTERS2[(letter_index + shift) % alphabet_length];
                break;
            }
        }
    }
    printf("%s\n", message);
}

void CSR_dec_math(char *message)
{
    int shift;
    if (!read_shift(&shift)) return;

    const int alphabet_length = strlen(LETTERS2);
    shift = (shift % alphabet_length + alphabet_length) % alphabet_length;

    size_t message_length = strlen(message);
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS2[letter_index]) {
                message[index] = LETTERS2[(letter_index - shift + alphabet_length) % alphabet_length];
                break;
            }
        }
    }
    printf("%s\n", message);
}

void CSR_enc_math(char *message)
{
    int shift;
    if (!read_shift(&shift)) return;

    const int alphabet_length = strlen(LETTERS2);
    shift = (shift % alphabet_length + alphabet_length) % alphabet_length;

    size_t message_length = strlen(message);
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS2[letter_index]) {
                message[index] = LETTERS2[(letter_index + shift) % alphabet_length];
                break;
            }
        }
    }
    printf("%s\n", message);
}
