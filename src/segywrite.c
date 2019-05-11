
#include <stdio.h>
#include <stdlib.h>

#include "segy.h"

int SEGYWRITE(const char *ofile, bhed re, segy tr, float *trace, int format, int endian, int cTrace)
/*
 * endian=0 for little endian machines, =1 for big endian machines
 * format=1  IBM     =5  IEEE
 * */
{
	FILE *ofp;
	long int fsize = 0;
	int ns = tr.ns;

	int it;
	float *data;
	data = (float *)malloc(ns*sizeof(float));

	for(it=0; it<ns; it++)
	{
		data[it] = trace[it];
	}

	if((ofp = fopen(ofile,"ab"))==NULL)
	{
		perror("Output oepn failed, when write segy file!\n");
		exit(0);
	}

	fseek( ofp, SEEK_SET, SEEK_END);
	fsize = ftell( ofp );
	
    if( fsize < (long int)sizeof(bhed)|| cTrace == 0 )
	{
		fclose( ofp );
		ofp = fopen( ofile, "wb" );
		re.format = format;

		if(endian==1)
		{
			swapbhed(&re);
		}

		fwrite( &re, sizeof(bhed), 1, ofp );
	}

	tr.tracr = cTrace + 1;

	if(endian==1) { swaphdrs( &tr ); }
	fwrite( &tr, sizeof(segy), 1, ofp );

	if(format==1) float_to_ibm( (int *)data, (int *)data, ns, endian );

	if(endian==1)
	{
		for(it=0; it<ns; it++)
		{
			swap_float_4(data+it);
		}
	}

	fwrite( data, sizeof(float), ns,ofp );
	free(data);
	fclose(ofp);

	return 0;
}

int SEGYWRITEF(bhed re, segy tr, float *trace, int format, int endian, int cTrace)
/*
 * endian=0 for little endian machines, =1 for big endian machines
 * format=1  IBM     =5  IEEE
 * */
{
	long int fsize = 0;
	int ns = tr.ns;

	int it;
	float *data;
	data = (float *)malloc(ns*sizeof(float));

	for(it=0; it<ns; it++)
	{
		data[it] = trace[it];
	}

	fseek( stdin, SEEK_SET, SEEK_END);
	fsize = ftell( stdout );
	
    if( fsize < (long int)sizeof(bhed)|| cTrace == 0 )
	{
		re.format = format;

		if(endian==1)
		{
			swapbhed(&re);
		}

		fwrite( &re, sizeof(bhed), 1, stdout );
	}

	tr.tracr = cTrace + 1;

	if(endian==1) { swaphdrs( &tr ); }
	fwrite( &tr, sizeof(segy), 1, stdout);

	if(format==1) float_to_ibm( (int *)data, (int *)data, ns, endian );

	if(endian==1)
	{
		for(it=0; it<ns; it++)
		{
			swap_float_4(data+it);
		}
	}

	fwrite( data, sizeof(float), ns, stdout );
	free(data);

	return 0;
}

int segywrite(const char *ofile, bhed re, segy tr, float *trace, int cTrace )
{
	FILE *ofp = NULL;
	long int fsize = 0;
	
	if((ofp = fopen(ofile,"ab"))==NULL)
	{
		perror("Output oepn failed, when write segy file!\n");
		exit(0);
	}

	fseek( ofp, SEEK_SET, SEEK_END);
	fsize = ftell( ofp );

    if( fsize < (long int)sizeof(bhed) || cTrace == 0 )
	{
		fclose( ofp );
		ofp = fopen( ofile, "wb" );
		re.format = 5;
		fwrite( &re, sizeof(bhed), 1, ofp );
	}

	tr.tracr = cTrace + 1;

	fwrite( &tr, sizeof(segy), 1, ofp );
	fwrite( trace, sizeof(float), re.hns, ofp );
		
	fclose(ofp);

	return 0;
}

int segywriteF(bhed re, segy tr, float *trace, int flag )
{
	if(stdout == NULL)
	{
		fprintf(stderr,"Output oepn failed, when write segy file!\n");
		exit(0);
	}

	if(!flag)
	{
		re.format = 5;
		fwrite( &re, sizeof(bhed), 1, stdout );
	}

	tr.tracr = flag + 1;

	fwrite( &tr, sizeof(segy), 1, stdout );
	fwrite( trace, sizeof(float), re.hns, stdout );
		
	return 0;
}
int segywriteFIBM(bhed re, segy tr, float *trace, int flag )
{
	int ns = tr.ns;
	int it;

	float *data;
	data = (float *)malloc(sizeof(float)*tr.ns);

	for(it=0; it<tr.ns; it++)
	{
		data[it] = trace[it];
	}

	if(stdout == NULL)
	{
		fprintf(stderr,"Output oepn failed, when write segy file!\n");
		exit(0);
	}

	if(!flag)
	{
		re.format = 1;
		swapbhed( &re );
		fwrite( &re, sizeof(bhed), 1, stdout );
	}

	tr.tracr = flag + 1;

	swaphdrs( &tr );
	fwrite( &tr, sizeof(segy), 1, stdout );

	float_to_ibm( (int *)data, (int *)data, ns, 1);

	for(it=0; it<ns; it++)
	{
		swap_float_4(data+it);
	}
	fwrite( data, sizeof(float), ns, stdout );
		
	free(data);
	return 0;
}
int segywriteIBM(const char *ofile, bhed re, segy tr, float *trace, int cTrace )
{
	FILE *ofp;
	long int fsize = 0;
	int ns = tr.ns;
	
	int it;

	float *data;
	data = (float *)malloc(sizeof(float)*tr.ns);

	for(it=0; it<tr.ns; it++)
	{
		data[it] = trace[it];
	}
	
	
	if((ofp = fopen(ofile,"ab"))==NULL)
	{
		perror("Output oepn failed, when write segy file!\n");
		exit(0);
	}

	fseek( ofp, SEEK_SET, SEEK_END);
	fsize = ftell( ofp );

  	if( fsize < (long int)sizeof(bhed)|| cTrace == 0 )
	{
		fclose( ofp );
		ofp = fopen( ofile, "wb" );

		re.format = 1;
		swapbhed( &re );
		fwrite( &re, sizeof(bhed), 1, ofp );
	}

	tr.tracr = cTrace + 1;

	swaphdrs( &tr );
	fwrite( &tr, sizeof(segy), 1, ofp );

	float_to_ibm( (int *)data, (int *)data, ns, 1);

	for(it=0; it<ns; it++)
	{
		swap_float_4(data+it);
	}

//	float_to_ibm((int *)data, (int *)data, ns, 1);

	fwrite( data, sizeof(float), ns,ofp );

	free(data);
		
	fclose(ofp);

	return 0;
}
