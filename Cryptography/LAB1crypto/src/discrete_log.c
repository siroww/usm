#include <stdio.h>
#include <stdlib.h>

#define LIMIT 32000

int read_int(const char *prompt, int *out_val);
int a_in_x_mod_p_eq_b(int a, int p, int b, int limit);
long long pow_mod(long long a, long long k, long long n);

int main(void)
{
    int a = 0, b = 0, p = 0;
    printf("The Discrete Logarithm Problem\n");
    printf(" a ^ x === b (mod p)\n");
    printf("Example: 31 ^ 5 === 3 (mod 29)\n");

    if (!read_int("Input a : ", &a) ||
        !read_int("Input b : ", &b) ||
        !read_int("Input p : ", &p)) {
        printf("Invalid input format. Only numeric digits are allowed.\n");
        return 1;
    }

    if (a < 1 || b < 1 || p < 1) {
        printf("Invalid input data. Only positive integers are accepted.\n");
        return 1;
    }

    int raspuns = a_in_x_mod_p_eq_b(a, p, b, LIMIT);
    if (raspuns >= 0) {
        printf("Result : %d\n\n", raspuns);
        printf(" %d ^ %d === %d (mod %d)\n", a, raspuns, b, p);
    } else {
        printf("No solution found.\n");
        printf("The discrete logarithm does not exist for the given parameters.\n");
    }
    return 0;
}

int read_int(const char *prompt, int *out_val)
{
    char buf[256];
    printf("%s", prompt);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        return 0;
    }

    char *endptr;
    long val = strtol(buf, &endptr, 10);
    while (*endptr == ' ' || *endptr == '\t' || *endptr == '\n' ||
           *endptr == '\r') {
        endptr++;
    }
    if (endptr == buf || *endptr != '\0') {
        return 0;
    }

    *out_val = (int)val;
    return 1;
}

int a_in_x_mod_p_eq_b(int a, int p, int b, int limit)
{
    for (int i = 1; i < limit; i++) {
        if (pow_mod(a, i, p) == b) {
            return i;
        }
    }
    return -1;
}

long long pow_mod(long long a, long long k, long long n)
{
    long long b_val = 1;
    while (k > 0) {
        if (k % 2 == 0) {
            k /= 2;
            a = (a * a) % n;
        } else {
            k--;
            b_val = (b_val * a) % n;
        }
    }
    return b_val;
}
