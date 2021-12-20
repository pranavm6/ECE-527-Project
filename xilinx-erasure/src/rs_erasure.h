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
//    This file contains the look up tables of RS Erasure codec
//Reference:
//    XAPP_XXX
///////////////////////////////////////////////////////////////////////////////
#ifndef _RS_ERASURE_H_
#define _RS_ERASURE_H_

#define GF_ORDER     8
#define NUM_CODES    4
#define NUM_EQUATION 4
#define NUM_TAPS     12
#define RSCODE_LEN   (NUM_TAPS+NUM_EQUATION)
#define NUM_ELEMENT  (NUM_TAPS*NUM_EQUATION)

//--------------------------------
// the main function declaration
//--------------------------------
void rs_erasure(unsigned char c[NUM_EQUATION], unsigned char d[NUM_TAPS], unsigned short survival_pattern, unsigned char codeidx);


#endif