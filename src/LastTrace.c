
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Judge current trace is last trace in the segy file or not
int LastTrace( int c_trace, int ntrace )
{
	if( c_trace != ntrace )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
