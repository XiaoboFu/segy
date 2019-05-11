
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Judge current trace is last trace of gather or not
int LastGather( int p_cdp, int n_cdp )
{
	if( p_cdp == n_cdp )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
