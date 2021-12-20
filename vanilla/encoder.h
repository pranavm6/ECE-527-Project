/*The following encoder implements Reed-Solomon Code: RS(144,128) where symbol size is 1 byte. The code can correct upto 8 errors that are NOT known ahead of time*/

#include <stdio.h>
#include <stdlib.h>
#include <field.h>

#define u32 unsigned int
#define N 144
#define K 128

/* Generator polynomial coeffients for (x-a)(x-a^2)(x-a^3)...*/
u32 g16[N-K+1] = {0};

/*Creates generator polynomial (x-a)(x-a^2)... where a is generator of GF(256)*/
u32 create_generator_polynomial();

/*Encodes data by multiplying with generator polynomial. Current implementation is the BCH-view of Reed Solomon codes and encoding is NOT systematic*/
u32 encode(u32 encoded[N],u32 data[K]);