/*        P-wave Amplitude Elliptical Fitting
 * Authors: Jiashun Yu, Xiaobo Fu, Xinran Fan, Jianlong Yuan, Chao Han
 * College of Geophysics, Chengdu University of Technology
 * Contact us,E-mail:xiaobo_foo@126.com
 * 		 10/10/2014
 *
 *	        File: swapbs.c
 *		Version: 1.0.0
 * */

#include <stdio.h>

/* Swap bytes function */
void swapbs(char *buf, short size){
        char tmp;
        switch (size){
                case 2:
                        tmp=buf[0]; buf[0]=buf[1]; buf[1]=tmp;
                        break;
                case 4:
                        tmp=buf[0]; buf[0]=buf[3]; buf[3]=tmp;
                        tmp=buf[1]; buf[1]=buf[2]; buf[2]=tmp;
                        break;
                case 8:
                        tmp=buf[0]; buf[0]=buf[7]; buf[7]=tmp;
                        tmp=buf[1]; buf[1]=buf[6]; buf[6]=tmp;
                        tmp=buf[2]; buf[2]=buf[5]; buf[5]=tmp;
                        tmp=buf[3]; buf[3]=buf[4]; buf[4]=tmp;
                        break;
                default:
                        break;
        }
}

void swap_short_2(short *tni2)
/**************************************************************************
 * swap_short_2            swap a short integer
 * ***************************************************************************/
{
 *tni2=(((*tni2>>8)&0xff) | ((*tni2&0xff)<<8));
}

void swap_u_short_2(unsigned short *tni2)
/**************************************************************************
 * swap_u_short_2          swap an unsigned short integer
 * ***************************************************************************/
{
 *tni2=(((*tni2>>8)&0xff) | ((*tni2&0xff)<<8));
}

void swap_int_4(int *tni4)
/**************************************************************************
 * swap_int_4              swap a 4 byte integer
 * ***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
            ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

void swap_u_int_4(unsigned int *tni4)
/**************************************************************************
 * swap_u_int_4            swap an unsigned integer
 * ***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
            ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

void swap_long_4(long *tni4)
/**************************************************************************
 * swap_long_4             swap a long integer
 * ***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
            ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

void swap_u_long_4(unsigned long *tni4)
/**************************************************************************
 * swap_u_long_4           swap an unsigned long integer
 * ***************************************************************************/
{
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
            ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

void swap_float_4(float *tnf4)
/**************************************************************************
 * swap_float_4            swap a float
 * ***************************************************************************/
{
 int *tni4=(int *)tnf4;
 *tni4=(((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
            ((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

void swap_double_8(double *tndd8)
/**************************************************************************
 * swap_double_8           swap a double
 * ***************************************************************************/
{
  char *tnd8=(char *)tndd8;
  char tnc;

  tnc= *tnd8;
  *tnd8= *(tnd8+7);
  *(tnd8+7)=tnc;

  tnc= *(tnd8+1);
  *(tnd8+1)= *(tnd8+6);
  *(tnd8+6)=tnc;

  tnc= *(tnd8+2);
  *(tnd8+2)= *(tnd8+5);
  *(tnd8+5)=tnc;

  tnc= *(tnd8+3);
  *(tnd8+3)= *(tnd8+4);
  *(tnd8+4)=tnc;
}
