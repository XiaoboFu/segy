/*
 * Authors: Jiashun Yu, Xiaobo Fu 
 *  E-mail: xiaobo_foo@126.com
 *         30/09/2014
 *
 * Version:1.0.0
 * */

#include <stdio.h>
#include <stdlib.h>

#include "segy.h"

void ibm_to_float(int from[], int to[], int n, int endian, int verbose)
/***********************************************************************
 * ibm_to_float - convert between 32 bit IBM and IEEE floating numbers
 ***********************************************************************
 * Input::
 * from		input vector
 * to		output vector, can be same as input vector
 * endian	byte order =0 little endian (DEC, PC's)
 * 		    =1 other systems
 ***********************************************************************
 *Notes:
 *Up to 3 bits lost on IEEE -> IBM
 *
 *Assumes sizeof(int) == 4
 *
 * IBM -> IEEE may overflow or underflow, taken care of by
 * substituting large number or zero
 *
 * Only integer shifting and masking are used.
 **********************************************************************
 * Credits: CWP: Brian Sumner,  c.1985
 **********************************************************************/
{
    	register int fconv, fmant, i, t;
    	for (i = 0;i < n; ++i) {
		fconv = from[i];
		/* if little endian, i.e. endian=0 do this */
		if (endian == 0) fconv = (fconv << 24) | ((fconv >> 24) & 0xff) |
			((fconv & 0xff00) << 8) | ((fconv & 0xff0000) >> 8);
		if (fconv) {
	    		fmant = 0x00ffffff & fconv;
	    		/* The next two lines were added by Toralf Foerster */
	    		/* to trap non-IBM format data i.e. conv=0 data  */
	 	   	if (fmant == 0) {
				if(verbose==2){ 
		 			printf("mantissa is zero data may not be in IBM FLOAT Format !");
		 			printf("setting fconv=0");
				}
				fconv=0;
	    		} 
			else {
		    		t = (int) ((0x7f000000 & fconv) >> 22) - 130;
	    			while (!(fmant & 0x00800000)) { 
					--t; fmant <<= 1; 
				}
	    			if (t > 254) 
					fconv = (0x80000000 & fconv) | 0x7f7fffff;
		    		else if (t <= 0) 
					fconv = 0;
		    		else 
					fconv =   (0x80000000 & fconv) | (t << 23) | (0x007fffff & fmant);
	  		}
		}
		to[i] = fconv;
    	}
}


void short_to_float(short from[], float to[], int n, int endian)
/****************************************************************************
 * short_to_float - type conversion for additional SEG-Y formats
 * *****************************************************************************
 * Author: Delft: J.W. de Bruijn, May 1995
 * Modified by: Baltic Sea Reasearch Institute: Toralf Foerster, March 1997
 * ****************************************************************************/
{
        register int i;

        if (endian == 0) {
                for (i = n - 1; i >= 0 ; --i) {
                        swap_short_2(&from[i]);
                        to[i] = (float) from[i];
                }
        } else {
                for (i = n - 1; i >= 0 ; --i)
                        to[i] = (float) from[i];
        }
}

void integer1_to_float(signed char from[], float to[], int n)
/****************************************************************************
 * integer1_to_float - type conversion for additional SEG-Y formats
 * *****************************************************************************
 * Author: John Stockwell,  2005
 * ****************************************************************************/
{
        while (n--) {
                to[n] = from[n];
        }
}

void int_to_float(int from[], float to[], int n, int endian)
/****************************************************************************
 * Author: J.W. de Bruijn, May 1995
 * ****************************************************************************/
{
        register int i;

        if (endian == 0) {
                for (i = 0; i < n; ++i) {
                        swap_int_4(&from[i]);
                        to[i] = (float) from[i];
                }
        } else {
                for (i = 0; i < n; ++i) {
                        to[i] = (float) from[i];
                }
        }
}

void float_to_ibm(int from[], int to[], int n, int endian)
/**********************************************************************
*  float_to_ibm - convert between 32 bit IBM and IEEE floating numbers
***********************************************************************
*  Input:
*  from       input vector
*  n          number of floats in vectors
*  endian     =0 for little endian machine, =1 for big endian machines
*
*  Output:
*  to         output vector, can be same as input vector
*
***********************************************************************
*  Notes:
*  Up to 3 bits lost on IEEE -> IBM
*
*  IBM -> IEEE may overflow or underflow, taken care of by
*  substituting large number or zero
*
*  Only integer shifting and masking are used.
***********************************************************************
*  Credits:     CWP: Brian Sumner
***********************************************************************/
{
		register int fconv, fmant, i, t;

		for (i=0;i<n;++i) 
		{
			fconv = from[i];
			if (fconv) 
			{
				fmant = (0x007fffff & fconv) | 0x00800000;
				t = (int) ((0x7f800000 & fconv) >> 23) - 126;
				while (t & 0x3) 
				{
					++t; 
					fmant >>= 1; 
				}
					
				fconv = (0x80000000 & fconv) | (((t>>2) + 64) << 24) | fmant;
			}
			if(endian==0)
				fconv = (fconv<<24) | ((fconv>>24)&0xff) |
						((fconv&0xff00)<<8) | ((fconv&0xff0000)>>8);
				
				to[i] = fconv;
		}
		
		return;
}
