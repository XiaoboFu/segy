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

void segy_convert( segy *tr_h, int big )
{
	if( big )
	{
		swaphdrs( tr_h );
	}

	return ;
}
