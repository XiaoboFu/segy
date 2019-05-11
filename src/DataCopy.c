#include <stdio.h>

#include "segy.h"

// Copy the trace head to the head buffer
int headCopy( segy *targ, segy from, int id )
{
	targ[id] = from;

	return 0;
}

// Copy the trace data to the trace buffer
int traceCopy( float *targ, float *from, int size, int id )
{
	int i;
	for( i=0; i<size; i++ )
	{
		targ[id*size+i] = from[i];
	}

	return 0;
}
