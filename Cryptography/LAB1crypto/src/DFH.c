#include <stdio.h>
#include "../include/globals.h"
#include "../include/random.h"

static long long modular_power(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base %= modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
}

void DIFFI_HELLMAN(void)
{
    long long p = randInt();
    long long g = 2;
    long long private_a;
    long long private_b;

    printf("Enter private key a: ");
    if (scanf("%lld", &private_a) != 1) return;
    printf("Enter private key b: ");
    if (scanf("%lld", &private_b) != 1) return;

    printf("Public parameters: p=%lld, g=%lld\n", p, g);
    printf("Private keys: a=%lld, b=%lld\n", private_a, private_b);

    long long public_a = modular_power(g, private_a, p);
    long long public_b = modular_power(g, private_b, p);
    printf("Public keys: A=%lld, B=%lld\n", public_a, public_b);

    long long shared_a = modular_power(public_b, private_a, p);
    long long shared_b = modular_power(public_a, private_b, p);
    printf("Shared keys: A=%lld, B=%lld\n", shared_a, shared_b);

    if (shared_a == shared_b) {
        printf("Shared key matches: %lld\n", shared_a);
    } else {
        printf("Error: shared keys do not match.\n");
    }
}
