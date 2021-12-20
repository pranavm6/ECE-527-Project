#ifndef _RS_ERASURE_H_
#define _RS_ERASURE_H_

#define GF_ORDER  8
#define ERRORS 32
#define DATA 32
#define DECODING_SIZE 4096


//--------------------------------
// the main function declaration
//--------------------------------
void validator(unsigned char c[ERRORS], unsigned char d[DATA]);


#endif
