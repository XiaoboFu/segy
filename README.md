# Segy
segy file Read-Write Library. 
Extract the core part from SU. However, the library only supports float-type segy data reading and writing. It can be used for personal scientific research, however production with caution.

This library is for my personal scientific research. There are some unknowns: bugs, but they don't affect my use.

# Install
cd src/

make

sudo make install

# Set Enviornment 
vi ~/.bashrc
export LD_LIBARAY_PATH=$LD_LIBARAY_PATH:'segy path'

# Demo from 
Note: src/test.c


/*************************************************************
 * File Name   : test.c
 * Author      : Xiaobo.Foo
 * E-mail      : xiaobo_foo@126.com
 * Created Time: Sat 06 Oct 2018 05:11:10 PM CST
 * CopyRight   : Xiaobo.Foo
 * Version     : 1.0
 * Description : 
 * **********************************************************/

#include <stdio.h>

#include <stdlib.h>

#include "../include/segy.h"


int main(int argc, char *argv[])

{

    bhed re;   // File head
    
    segy tr;   // Trace head

    int dt;    // time sample interva unit:us
    int ns;    // number of samples for one trace
    int ntr;   // number of trace

    // get segy file information
    getSgyInfo(argv[1], &re, &ntr, &ns, &dt);
    // trace array
    float trace[ns];
    int itr;

    for(itr=0; itr<ntr; itr++)
    {
        // read data
        segyread(argv[1], &tr, trace, itr);
        // write data
        segywriteIBM(argv[2],re, tr, trace,itr);
    }


    return 0;
}


For more: xiaobo_foo@126.com
