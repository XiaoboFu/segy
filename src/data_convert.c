/* ---------------------------------------------------------------*
 * |         	   	    AVAz				| *
 * |								| *
 * |          P-wave Amplitude Elliptical Fitting		| *
 * |	    developed by College of Geophysics(CDUT)		| *
 * |								| *
 * |		     ALL Rights Reserved			| *
 * |								| *
 * |------------------------------------------------------------| *
 * ****************************************************************
 * AVAz Module:
 * -----------------
 * ..Module name   : data_convert
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

void data_convert(float *seis_data, int tr_len, int big, int format )
{
	int it;

	if( big && format == 1 )
	{
		ibm_to_float( (int *)seis_data, (int *)seis_data, tr_len, 0, 0 );
	}
	if( big && format == 5 )
	{
		for( it = 0; it < tr_len; it++ )
		{
			swapbs((char*)(seis_data+it) , 4);
		}
	}

	return ;
}
