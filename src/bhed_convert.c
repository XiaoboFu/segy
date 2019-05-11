/* ---------------------------------------------------------------*
 * |         	   	    SEGY				| *
 * |								| *
 * |          P-wave Amplitude Elliptical Fitting		| *
 * |	    developed by College of Geophysics(CDUT)		| *
 * |								| *
 * |		     ALL Rights Reserved			| *
 * |								| *
 * |------------------------------------------------------------| *
 * ****************************************************************
 * SEGY Module:
 * -----------------
 * ..Module name   : bhed_convert
 * ..Version number: 1.5.16
 * ..Language      : C
 * ..Author        : Jiashun Yu, Xiaobo Fu (CDUT)
 * ..Date          : 2015.05.28
 * ..E-mail        : xiaobo_foo@126.com
 * ..
 * ..++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * . Revision table:
 * ------------------
 * . 	version    :
 * 	Description:
 * 	Author     :
 * 	Date       :
 * .+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *   Function: data_convert
 * ------------------
 *   This module is to data convert the AVAz module parameters
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *   Parameters    :
 *  -----------------
 *
 * */

#include <stdio.h>

#include "segy.h"

void bhed_convert( bhed *re_h, int *big )
{
	if( re_h->format > 255 )
	{
		*big = 1;
		swapbhed( re_h );
	}
	else
	{
		*big = 0;
	}

	return ;
}
