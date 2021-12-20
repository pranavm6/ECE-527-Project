/*The following encoder implements Reed-Solomon Code: RS(144,128) where symbol size is 1 byte. The code can correct upto 8 errors that are NOT known ahead of time*/

#include <stdio.h>
#include <stdlib.h>
#include <field.h>

#define u32 unsigned int
#define N 144
#define K 128

u32 syndromes[N-K];

u32 calculate_syndromes();