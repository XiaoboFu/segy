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
 * ..Module name   : getSgyInfo
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
 *   Function: get segy information
 * ------------------
 *   This module is to get segy information the AVAz module parameters
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *   Parameters    :
 *  -----------------
 *
 * */

#include <stdio.h>
#include <stdlib.h>

#include "segy.h"

static char header[3200]={"\
C01 This tape was made at the SEGY                                              \
C02                                                                             \
C03 This SEGY file module is a standard IBM/IEEE format.                        \
C04 All segy file format would be transform IBM/IEEE format.                    \
C05                                                                             \
C06 The segy lib made by Xiaobo Foo(CDUT).                                      \
C07                                                                             \
C08 This 3200 bytes ebcdic made in getSgyInfo. And you can change it.           \
C09 See getSgyInfo.c: \"header\". If you had changed the source, you should       \
C10 complie it again. How to use the module, you should add the header:         \
C11 #include \"segy.h\".                                                          \
C12                                                                             \
C13 How to complile the SEGY library?                                           \
C14 cd src; make                                                                \
C15                                                                             \
C16 Add the envirnment to your .bashrc or others                                \
C17 export SEGY=/home/fxb/Softeware/SEGY/                                       \
C18                                                                             \
C19 How to complile your programme?                                             \
C20 gcc yoursourcename -I$SEGY/include -L$SEGY/lib -lsegy                       \
C21                                                                             \
C22                                                                             \
C23 About us?                                                                   \
C24 Chengdu University of Technology, College of Geophysics                     \
C25 Jiashun Yu Laboratory,                                                      \
C26 Principal Adviser: Jiashun.Yu                                               \
C27 Author: Xiaobo.Foo                                                          \
C28                                                                             \
C29                                                                             \
C30 Contact us: E mail: xiaobo_foo@126.com                                      \
C31                 QQ: 649294261                                               \
C32              Phone: 15881053339                                             \
C33 Made this module at:2015.11.06                                              \
C34 Modify this module at: 2016.06.17                                           \
C35 Modify this module at: 2016.11.21                                           \
C36                                                                             \
C37                                                                             \
C38                                                                             \
C39                                                                             \
C40 END EBCDIC                                                                  "
};

int getSgyInfo(const char *ifile , bhed *re, int *ntrace, int *ns, int *dt )
{	
	FILE *ifp=NULL;

   	long int fsize = 0 ;

	if((ifp = fopen(ifile,"rb"))==NULL)
	{
		fprintf(stderr,"----------------------------------------------------------------\n");
		fprintf(stderr," Sorry, open the %s file failed, when get segy info!\n",ifile);
		fprintf(stderr,"----------------------------------------------------------------\n");
		return EXIT_FAILURE;
	}

	fseek ( ifp, SEEK_SET, SEEK_END );/* seek from the start to the end */
	fsize    = ftell( ifp );	/* get the size of the segy file */
	

	rewind(ifp);

	fread ( re, 3600, 1, ifp );

	if( re->format > 255 ) 
	{
		swapbhed( re );
	}

	int i, j;
	for( i=0; i<40; i++ )
	{
		for( j=0; j<80; j++ )
		{
			int index = i*80+j;
			re -> commend[index] = header[index];
		}
	}

//	fprintf(stderr,"Format = %d\n",re->format);
	
//	re->format = 5;
	/* get the trace length */
	*ns = re -> hns;

	/* get the traces of the seismic wave data */
	*ntrace = ( fsize - 3600 ) / ( 240+sizeof(float)*(*ns) );

	*dt = re->hdt;

	if(ifp!=NULL){
		fclose(ifp);
	}

	return 0;
}

/* stdin */
int getSgyInfoF( bhed *re, int *ntrace, int *ns, int *dt )
{	
	rewind(stdin);
    	long int fsize = 0 ;

	if(stdin == NULL)
	{
		perror("Sorry, open the seismic data failed, when get segy info!\n");
		return EXIT_FAILURE;
	}

	fseek ( stdin, SEEK_SET, SEEK_END );/* seek from the start to the end */
	fsize    = ftell( stdin );	/* get the size of the segy file */
	
	rewind(stdin);

	fread ( re, 3600, 1, stdin);

	if( re->format > 255 )
        {
                swapbhed( re );
        }

	int i, j;
	for( i=0; i<40; i++ )
	{
		for( j=0; j<80; j++ )
		{
			int index = i*80+j;
			re -> commend[index] = header[index];
		}
	}

//	fprintf(stderr,"Format = %d\n",re->format);
	
//	re->format = 5;
	/* get the trace length */
	*ns = re -> hns;
	/* get the traces of the seismic wave data */
	*ntrace = ( fsize - 3600 ) / ( 240+sizeof(float)*(*ns) );

	*dt = re->hdt;

	return 0;
}

int getShotInfo(char *ifile, int *NS, int *NG, \
				int *sxbeg, int *szbeg, int *gxbeg, int *gzbeg,\
				int *dsx, int *dsz, int *dgx, int *dgz)
{
	*NS = *NG = *sxbeg = *szbeg = 0;
	*dsx = *dgx = *gxbeg = *gzbeg = 0;
	*dsz = *dgz = 0;

	int firstEp = 0;
	FILE *ifp;
	ifp = fopen(ifile, "rb" );
	if(ifp == NULL)
	{ 
		fprintf(stderr,"|-----------------------------------------------------|\n");
		fprintf(stderr,"| Sorry, can't open the file of %s. |\n",ifile);
		fprintf(stderr,"|-----------------------------------------------------|\n");
		return EXIT_FAILURE;
	}
	
	bhed re;
	segy tr;
	int big = 0;
	fread( &re, 3600, 1, ifp );
	bhed_convert( &re, &big  );

	int ntrace = 0;
	int ns = 0;
	int fsize;

	fseek( ifp, SEEK_SET, SEEK_END );
	fsize = ftell( ifp );
	ns = re.hns;
	ntrace = ( fsize - 3600 ) / ( 240 + 4 * ns );

	float *trace=NULL; trace = (float *)malloc(4*ns);

	int cep=-1;
	int itr = 0;
	for(itr=0; itr<ntrace; itr++)
	{
		fread( &tr, 240, 1, ifp );
		fread( trace, ns, 4, ifp );

		segy_convert( &tr, big );
		data_convert( trace, ns, big, re.format );

		if(cep != tr.ep)
		{
			*NS = *NS + 1;
			cep = tr.ep;
		}
		if(itr==0)
		{
			*sxbeg = tr.sx;
			*szbeg = tr.sy;
			*gxbeg = tr.gx;
			*gzbeg = tr.gy;
			firstEp = tr.ep;
		}
		
		if(firstEp == tr.ep)
		{
			*NG = *NG + 1;
		}
	}

	int sxend = tr.sx;
	int szend = tr.sy;
	int gxend = tr.gx;
	int gzend = tr.gy;
	*dsx = (sxend - *sxbeg)/(*NS);
	*dsz = (szend - *szbeg)/(*NS);
	*dgx = (gxend - *gxbeg)/(*NG);
	*dgz = (gzend - *gzbeg)/(*NG);


	free(trace);
	fclose(ifp);

	return 0;
}
