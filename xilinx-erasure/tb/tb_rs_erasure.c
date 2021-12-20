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
//    This file contains the testbench for RS Erasure Codedc.
//Reference:
//    XAPP_XXX
///////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include "../src/rs_erasure.h"


int main(void){

	int k, i;
	char test_pass;

	FILE* fp=NULL;
	fp=fopen("tv_rs_erasure_in.txt", "rt");
	if(NULL==fp){
		printf("Error Opening Input Test Vector!\n");
		return(1);
	}
	
	FILE* fp_gold=NULL;
	fp_gold=fopen("tv_rs_erasure_mout.txt", "rt");
	if(NULL==fp_gold){
		printf("Error Opening Golden Output Test Vector!\n");
		return(1);
	}
	
	int a[NUM_TAPS+2]; // 2 is survival pattern and code id
	
	int fileend=0;
	
	unsigned char c[NUM_EQUATION];
	unsigned char d[NUM_TAPS];

	unsigned short survival_pattern;
	unsigned char  codeid;

	int errcnt       = 0;
	int linecnt      = 0;
	int suberrcnt[NUM_CODES];
	int sublincnt[NUM_CODES];
	
	
	for(i=0;i<NUM_EQUATION;i++) suberrcnt[i]=0;
	for(i=0;i<NUM_EQUATION;i++) sublincnt[i]=0;
	
	
	while(1){
		
		// read the data in
		// each line is codeid, survival pattern, data(1:12)
		for(k=0;k<(NUM_TAPS+2);k++){
			 int tmp;
			 int scnt = fscanf(fp, "%d", &tmp);
			 a[k] = tmp;

			 if (scnt < 0) {
				 fileend = 1;
				 break;
			 }
		}
		
		// quit the loop at the file end
		if(fileend) break;
		linecnt++;
		
		// process the data
		codeid = a[0]&3;
		survival_pattern = a[1]&((1<<RSCODE_LEN)-1);
		for(k=0;k<12;k++) d[k]=a[2+k]&((1<<GF_ORDER)-1);
		
		rs_erasure(c, d, survival_pattern, codeid);

		sublincnt[codeid]++;
		
		// read data from golden test vector
		unsigned char this_is_err=0;
		
		for (k = 0;k < NUM_EQUATION; k++) {
				int tmp;
				fscanf(fp_gold, "%d", &tmp);
				if (c[k] != tmp){
					this_is_err=1;
					// print 5 errors for each codeid
					if(suberrcnt[codeid]<=5)
						printf("[Err %3d] line %d\n", errcnt, linecnt);
				}
		}
		
		if(this_is_err){
			suberrcnt[codeid]++;
			errcnt++;
		}	
					
	}
	
	fclose(fp);
	fclose(fp_gold);

	for(i=0;i<NUM_CODES;i++){
			printf("\t[%d] %3d out of %3d test vectors failed.\n", i, suberrcnt[i], sublincnt[i]);
	}
	printf("Total %d Test Vectors, Err Count = %d.\n", linecnt, errcnt);
	if (errcnt) printf("Test Failed!\n");
	else printf("Test Passed!\n");

	return(errcnt);
	

}

