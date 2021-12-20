#define u32 unsigned int

#include <stdio.h>
#include <stdlib.h>

/*Add operator for two numbers. For any GF(2^n), it will be a xor. Add is same as subtract*/
u32 add(u32 a, u32 b);

/*Multiply operator for two numbers. Uses precomputed log and anti-log tables to compute a*b = anti-log(log(a)+log(b)*/
u32 multiply(u32 a, u32 b);

/*Get anti-log table*/
u32* get_alogx();