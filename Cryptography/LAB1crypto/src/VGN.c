#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/globals.h"

void VGN_encript(char *message)
{
    int message_value = 0;
    int key_value = 0;
    char key[26];
    printf("Enter key: ");
    if (scanf("%25s", key) != 1) return;

    const size_t message_length = strlen(message);
    const int alphabet_length = (int)strlen(LETTERS3);
    const size_t key_length = strlen(key);
    char *encrypted = malloc(message_length + 1);
    if (encrypted == NULL) {
        fprintf(stderr, "Could not allocate output buffer.\n");
        return;
    }

    size_t key_position = 0;
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS3[letter_index]) {
                message_value = letter_index;
            }
            if (key[key_position] == LETTERS3[letter_index]) {
                key_value = letter_index;
            }
        }
        encrypted[index] = LETTERS3[(message_value + key_value) % alphabet_length];
        key_position = (key_position + 1) % key_length;
    }
    encrypted[message_length] = '\0';
    printf("%s\n", encrypted);
    free(encrypted);
}

void VGN_enc_seed(char *message)
{
    int message_value = 0;
    int key_value = 0;
    char key[26];
    printf("Enter key: ");
    if (scanf("%25s", key) != 1) return;

    const unsigned int seed = 1644485555;
    srand(seed);

    const size_t message_length = strlen(message);
    const int alphabet_length = (int)strlen(LETTERS3);
    const size_t key_length = strlen(key);
    char *encrypted = malloc(message_length + 1);
    if (encrypted == NULL) {
        fprintf(stderr, "Could not allocate output buffer.\n");
        return;
    }

    size_t key_position = 0;
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS3[letter_index]) {
                message_value = letter_index;
            }
            if (key[key_position] == LETTERS3[letter_index]) {
                key_value = letter_index;
            }
        }

        const int key_shift = (key_value + rand() % 3) % alphabet_length;
        encrypted[index] = LETTERS3[(message_value + key_shift) % alphabet_length];
        key_position = (key_position + 1) % key_length;
    }
    encrypted[message_length] = '\0';
    printf("seed: %u | result: %s\n", seed, encrypted);
    free(encrypted);
}

void VGN_decript(char *message)
{
    int message_value = 0;
    int key_value = 0;
    char key[26];
    printf("Enter key: ");
    if (scanf("%25s", key) != 1) return;

    const size_t message_length = strlen(message);
    const int alphabet_length = (int)strlen(LETTERS3);
    const size_t key_length = strlen(key);
    char *decrypted = malloc(message_length + 1);
    if (decrypted == NULL) {
        fprintf(stderr, "Could not allocate output buffer.\n");
        return;
    }

    size_t key_position = 0;
    for (size_t index = 0; index < message_length; index++) {
        for (int letter_index = 0; letter_index < alphabet_length; letter_index++) {
            if (message[index] == LETTERS3[letter_index]) {
                message_value = letter_index;
            }
            if (key[key_position] == LETTERS3[letter_index]) {
                key_value = letter_index;
            }
        }

        decrypted[index] = LETTERS3[(message_value - key_value + alphabet_length) % alphabet_length];
        key_position = (key_position + 1) % key_length;
    }
    decrypted[message_length] = '\0';
    printf("%s\n", decrypted);
    free(decrypted);
}
