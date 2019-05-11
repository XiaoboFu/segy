#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "segy.h"

int segyread(const char *ifile , segy *tr, float *trace, int cTrace )
{	
	FILE *ifp = NULL;

	bhed re;

	int it = 0;
	int ns = 0 ;
	int ntrace = 0 ;
	long fsize = 0 ;
	int big    = 0 ;

	if((ifp = fopen(ifile,"rb"))==NULL)
	{
		fprintf( stderr, "-------------------------------------------------------------------------\n");
		fprintf( stderr, " Sorry, cannot open the %s file, when read segy file.! \n", ifile );
		fprintf( stderr, "-------------------------------------------------------------------------\n");
		exit(0);
	}
	
	fread ( &re, 3600, 1, ifp );

	if( re.format > 255 )
	{
		big = 1;
		swapbhed( &re );
	}
	else
	{
		big = 0; 
	}

	ns = re.hns;		/* get the trace length */

	fseek ( ifp, 0, 2 );		/* seek from the start to the end */
	fsize = ftell( ifp );		/* get the size of the segy file */

	/* get the traces of the seismic wave data */
	ntrace = ( fsize - 3600 ) / ( 240+sizeof(float)*ns );

	if(cTrace > ntrace)
	{
		fprintf( stderr, "|----------------------------------------------|\n");
		fprintf( stderr, "| Sorry, the segy is to end. Not enough trace. |\n");
		fprintf( stderr, "|----------------------------------------------|\n");

		return 1;
	}

	rewind( ifp );		/* file pointer return to the file start */

	/* skip 3600 bytes from the file start */
	fseek ( ifp, 3600L + ( 240L + 4L * (long)ns ) *(long) cTrace , 0 );
	
	/* read the segy traces head of 240 bytes */
	fread ( tr, 240, 1, ifp );
	if( big )
	{
       	swaphdrs( tr );
	}

	/* read the seismic data from the segy file */	
	fread( trace, sizeof(float)*ns, 1, ifp );

	fclose(ifp);

	if( re.format == 1 )
	{
		ibm_to_float( (int *)trace, (int *)trace, ns, !big, 0 );
		
		return 1;
	}
	else if( big && re.format == 5 )
	{
		for( it = 0; it < ns; it++ )
		{
			swapbs((char*)(trace + it) , 4);
		}
		
		return 1;
	}
	else if(re.format == 2)
	{
		int_to_float((int *)trace, (float *)trace, ns, !big );
	}
	else if(re.format == 3)
	{
		short_to_float((short *)trace, (float *)trace, ns, !big );
	}
	else
	{
		return 1;
	}

	return 0;
}

int segyreadF(segy *tr, float *trace, int cTrace )
{	
	rewind(stdin);
	bhed re;

	int it = 0;
	int ns = 0 ;
	int ntrace = 0 ;
	long fsize = 0 ;
	int big    = 0 ;

	if(stdin == NULL)
	{
		perror("Sorry, cannot open the seismic data file, when read segy file!");
		exit(0);
	}
	
	fread ( &re, 3600, 1, stdin );

	if( re.format > 255 )
	{
		big = 1;
		swapbhed( &re );
	}
	else
	{
		big = 0; 
	}

	ns = re.hns;		/* get the trace length */

	fseek ( stdin, 0, 2 );		/* seek from the start to the end */
	fsize = ftell( stdin );		/* get the size of the segy file */

	/* get the traces of the seismic wave data */
	ntrace = ( fsize - 3600 ) / ( 240+sizeof(float)*ns );

	if(cTrace > ntrace)
	{
		fprintf( stderr, "|----------------------------------------------|\n");
		fprintf( stderr, "| Sorry, the segy is to end. Not enough trace. |\n");
		fprintf( stderr, "|----------------------------------------------|\n");

		return 1;
	}

	rewind( stdin );		/* file pointer return to the file start */

	/* skip 3600 bytes from the file start */
	fseek ( stdin, 3600L + ( 240L + 4L * (long)ns ) *(long) cTrace , 0 );
	
	/* read the segy traces head of 240 bytes */
	fread ( tr, 240, 1, stdin);
	if( big )
	{
		swaphdrs( tr );
	}

	/* read the seismic data from the segy file */	
	fread( trace, sizeof(float)*ns, 1, stdin);

	if( re.format == 1 )
	{
		ibm_to_float( (int *)trace, (int *)trace, ns, !big, 0 );
		return 1;
	}
	else if( big && re.format == 5 )
	{
		for( it = 0; it < ns; it++ )
		{
			swapbs((char*)(trace + it) , 4);
		}
		
		return 1;
	}
	else if(re.format == 2)
	{
		int_to_float((int *)trace, (float *)trace, ns, !big );
	}
	else if(re.format == 3)
	{
		short_to_float((short *)trace, (float *)trace, ns, !big );
	}
	else
	{
		return 1;
	}

	return 0;
}

