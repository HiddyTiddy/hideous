/*
 * generates pseudo random numbers using a linear congruent generator
 * might be not accurate or anything
 * but works?
 * or doesn't idk 
 */

#include <stdio.h>

/*
 * magic
 * https://stackoverflow.com/questions/1205506/calculating-a-round-order-of-magnitude
 */
unsigned int baseTwoDigits(unsigned int x) {
    return x ? 32 - __builtin_clz(x) : 0;
    // ????
}

static unsigned int baseTenDigits(unsigned int x) {
    static const unsigned char guess[33] = {
        0, 0, 0, 0, 1, 1, 1, 2, 2, 2,
        3, 3, 3, 3, 4, 4, 4, 5, 5, 5,
        6, 6, 6, 6, 7, 7, 7, 8, 8, 8,
        9, 9, 9
    };
    static const unsigned int tenToThe[] = {
        1, 10, 100, 1000, 10000, 100000, 
        1000000, 10000000, 100000000, 1000000000,
    };
    unsigned int digits = guess[baseTwoDigits(x)];
    return digits + (x >= tenToThe[digits]);
}

unsigned int max(unsigned int a, unsigned int b) {
    if (a < b) return b;
    return a;
}

unsigned long long pow10(unsigned int exponent, unsigned long long modulo) {
    unsigned long long out = 1;
    for(size_t i=0; i<exponent; i++) {
        out *= 10;
        out %= modulo;
    }
    return out;
}

// stolen and rewritten from https://gist.github.com/kebunit/4fa83273090837fc1157
unsigned long long
mult(unsigned long long a,
     unsigned long long b,
     unsigned long long m)
{
    a = a % m;
    b = b % m;
    unsigned int N = max(baseTenDigits(a), baseTenDigits(b));
    if (N < 10) return (a * b) % m;
    N = N/2 + N%2;

    unsigned long long multiplier = pow10(N, m) % m; // %m not needed
    unsigned long long B = a / multiplier;
    unsigned long long A = a - (B * multiplier); // ?
    unsigned long long D = b / multiplier;
    unsigned long long C = b - (D * multiplier); // or d * N, idk really

    unsigned long long z0 = mult(A,C, m);
    unsigned long long z1 = mult(A+B, C + D, m);
    unsigned long long z2 = mult(B,D,m);

    return (z0
            + ((z1-z0-z2) * multiplier) % m
            + (z2 * pow10(2*N, m))      % m
           ) % m;
}

void testMult(unsigned long long a, unsigned long long b, unsigned long long m) {
    printf("%llu == %llu\n", (a*b)%m, mult(a,b,m));
}

// https://www.ams.org/journals/mcom/1999-68-225/S0025-5718-99-00996-5/S0025-5718-99-00996-5.pdf
unsigned long long random_state = 69;
// 2^63 - 25 is the largest prime that plays "nice" with being multiplied
#define RAND_M 9223372036854775751UL
#define RAND_A 4373305567859904186UL
#define RAND_C 7 % RAND_M
// c value is not quite that important apparently as long as gcd(c,m) = 1

unsigned long long rand() {
    random_state = (mult(RAND_A, random_state, RAND_M) + RAND_C) % RAND_M;
    return random_state;
}

int main() {
    for (int i = 0; i < 100; i++) {
        printf("%llu\n", rand());
    }
    return 0;
}
