#ifndef INCLUDE_RANDOM_H
#define INCLUDE_RANDOM_H

#include "config.h"

typedef struct suite {
    int* suite;
    int taille;
} suite_t;

suite_t* suite_new(uint taille);
void suite_delete(suite_t* suite);
int is_prime(uint a);
int is_knuth(uint a, uint c, uint m);
suite_t* pseudo(uint a, uint c, uint m, uint x);
int pgcd(int a, int b);

#endif
