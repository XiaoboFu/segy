/*************************************************************
 * File Name   : test.c
 * Author      : Xiaobo.Foo
 * E-mail      : xiaobo_foo@126.com
 * Created Time: Sat 06 Oct 2018 05:11:10 PM CST
 * CopyRight   : Xiaobo.Foo & Yu's Team
 * Version     : 0.0.1
 * Description : 
 * **********************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include "../include/segy.h"


int main(int argc, char *argv[])
{
	bhed re;
	segy tr;

	int dt;
	int ns;
	int ntr;

	getSgyInfo(argv[1], &re, &ntr, &ns, &dt);

	float trace[ns];
	int itr;

	for(itr=0; itr<ntr; itr++)
	{
		segyread(argv[1], &tr, trace, itr);
		segywriteIBM(argv[2],re, tr, trace,itr);
	}


	return 0;
}
