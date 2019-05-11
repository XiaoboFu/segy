/* Filename: pickCDPgather.c
 *   Author: Xiaobo Foo
 *     From: Yu's Lab, CDUT
 *     Date: 2016/07/15
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "segy.h"

int pickCDPgather(const char *file, segy *trBuf,  float *traceBuf, long int *size, int *ntr, int *flag )
{
	FILE *ifp=NULL;
	if((ifp = fopen( file, "rb" ))==NULL)
	{
		puts("\n");
		fprintf(stderr,"-----------------------------------------------------\n");
		fprintf(stderr," Sorry, can't open the file of %s.\n",file);
		fprintf(stderr,"-----------------------------------------------------\n");
		puts("\n");
		exit(0);
	}

	bhed re;
	segy tr;
	int big;
	fread( &re, 3600, 1, ifp );
	bhed_convert( &re, &big  );

	int ntrace = 0;
	int ns = 0;

	long int fsize;
	fseek( ifp, SEEK_SET, SEEK_END );
	fsize = ftell( ifp );
    ns = re.hns;
    ntrace = ( fsize - 3600 ) / ( 240 + 4 * ns );
	
	if( *size<3600 )
	{
		*size = 3600L;
	}
	fseek( ifp, *size, SEEK_SET );

	float *trace=NULL; trace = (float *)malloc(4*ns);
	
	int cdp=0;
	int itr = 0;
	for( itr=0; itr<ntrace; itr++ )
	{
		fread( &tr, 240, 1, ifp );
		fread( trace, ns, 4, ifp );
		
		segy_convert( &tr, big );
		data_convert( trace, ns, big, re.format );

		if( itr==0 ) cdp = tr.cdp;

		if( tr.cdp == cdp )
		{
			headCopy ( trBuf,  tr, itr  );
			traceCopy( traceBuf, trace, ns, itr );
		}
		else
		{
			fseek( ifp, -4L*ns-240L, SEEK_CUR );
			*size = ftell( ifp );
			*flag = 0;
			*ntr = itr;
			break;
		}

		if( fsize==ftell(ifp) )
		{
			*flag = 1;
			*ntr = itr + 1;
			break;
		}
	}

	free(trace);

	fclose(ifp);

	return 0;
}



int pickCDPgatherF( segy *trBuf,  float *traceBuf, long int *size, int *ntr, int *flag )
{
	rewind(stdin);
	if(stdin == NULL)
	{
		perror("Sorry, can't open the seismic data file in pickCDPgatherF!");
		exit(0);
	}

	bhed re;
	segy tr;
	int big;
	fread( &re, 3600, 1, stdin );
	bhed_convert( &re, &big  );

	int ntrace = 0;
	int ns = 0;

	long int fsize;
	fseek( stdin, SEEK_SET, SEEK_END );
	fsize = ftell( stdin );
        ns = re.hns;
        ntrace = ( fsize - 3600 ) / ( 240 + 4 * ns );
	
	if( *size<3600 )
	{
		*size = 3600L;
	}
	fseek( stdin, *size, SEEK_SET );

	float *trace=NULL; trace = (float *)malloc(4*ns);
	
	int cdp=0;
	int itr = 0;
	for( itr=0; itr<ntrace; itr++ )
	{
		fread( &tr, 240, 1, stdin );
		fread( trace, ns, 4, stdin );
		
		segy_convert( &tr, big );
		data_convert( trace, ns, big, re.format );

		if( itr==0 ) cdp = tr.cdp;

		if( tr.cdp == cdp )
		{
			headCopy ( trBuf,  tr, itr  );
			traceCopy( traceBuf, trace, ns, itr );
		}
		else
		{
			fseek( stdin, -4*ns-240, SEEK_CUR );
			*size = ftell( stdin );
			*flag = 0;
			*ntr = itr;
			break;
		}

		if( fsize==ftell(stdin) )
		{
			*flag = 1;
			*ntr = itr + 1;
			break;
		}
	}

	free(trace);

	return 0;
}
