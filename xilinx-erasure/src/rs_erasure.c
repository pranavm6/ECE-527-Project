///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2015 Xilinx, Inc.
// All Rights Reserved
///////////////////////////////////////////////////////////////////////////////
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: 1.0
//  \   \         Application : Vivado HLS
//  /   /         Filename: filt_coef_rom.h
// /___/   /\     Timestamp: Tue Aug 11 5:00:00 PST 2015
// \   \  /  \
//  \___\/\___\
//
//Command: N/A
//Device:  xcku035-fbva676-2-i
//Design Name: RSErasure
//Purpose:
//    This file contains the main function of RS Erasure codec.
//Reference:
//    XAPP_XXX
///////////////////////////////////////////////////////////////////////////////

#include "rs_erasure.h"
#include "rs_roms.c"

// main function
void rs_erasure(unsigned char c[NUM_EQUATION], unsigned char d[NUM_TAPS], unsigned short survival_pattern, unsigned char codeidx){

	unsigned char i;
	unsigned char j;
	unsigned char k;
	unsigned char r[NUM_ELEMENT]; // 4 x 12
	
	// get the base address of the decoding rom
	unsigned short decmat_idx = DECMAT_BA[codeidx&3];
	
	
	//---------------------------------------
	// go through the survival pattern bit by bit
	// find the dec_mat index
	//---------------------------------------
	
	//
	// translate the survival pattern into erasure pattern
	// err_mask ensures the unused bits remain 0
	unsigned short erasure_pattern = survival_pattern^((1<<RSCODE_LEN)-1);
	
	// pad 1's to the msb of the error pattern
	unsigned char  padlen  = (3^(codeidx&3))<<1;
	unsigned short padmask = ((1<<padlen)-1)<<(RSCODE_LEN-padlen);
	unsigned short errpat  = erasure_pattern | padmask;
	
	// Initialize the number of remaining ones = (p+1)
	char p = NUM_EQUATION-1 + padlen; 
	
  // Scan the bits of errpat from MSB to LSB
	for(k=0; k<RSCODE_LEN; k++){

		// number of remaining bits = (L+1)
		unsigned char L = (k^0xf)&0xf;
	
		// extract the msb of the remaining bits
		unsigned char msb = (errpat>>(RSCODE_LEN-1))&1;

		//if this bit is 0, then count the number of integers larger than it
		//if this bit is 1, decrease p by 1
		if (msb) p--;
		else if(p>=0) decmat_idx+=F_tbl[((p&3)<<4) | (L&0xf)];

		// dump the msb and move to the next bit
		errpat=(errpat<<1);
	}
	
	//---------------------------------------
	// dot multiply the decoding matrix with
	// survived data blocks
	//---------------------------------------

	// initialize the decoding matrix polynomial
	for(k=0;k<NUM_ELEMENT;k++) r[k] = DECMAT_ROM[decmat_idx][k];

	// reset all the code bits
	for(k=0; k<NUM_EQUATION; k++) c[k] = 0;
		
	// loop for all the bits of the input data
	for(i=0; i<GF_ORDER; i++){
			// loop for all 8 data
			for(j=0; j<NUM_TAPS; j++)
				// loop for all 4 code symbols
				for(k=0; k<NUM_EQUATION; k++){
					unsigned char idx = k*NUM_TAPS+j;
					unsigned char  tmp = r[idx];
					// update c
					c[k] = c[k] ^  ( ((d[j]>>i)&1)? tmp : 0 );
					// update ram
					r[idx] = ((tmp>>7)&1) ?  ((tmp<<1)^gf_poly) : (tmp<<1);
					
				}
		
	}

}

