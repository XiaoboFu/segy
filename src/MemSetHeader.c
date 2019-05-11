#include <stdio.h>

#include "segy.h"

static char header[3200]={"\
C01 This tape was made at the SEGY                                              \
C02                                                                             \
C03 This SEGY file module is a standard IBM/IEEE format.                        \
C04 All segy file format would be transform IBM/IEEE format.                    \
C05                                                                             \
C06 The segy lib made by Xiaobo Foo(CDUT).                                      \
C07                                                                             \
C08 This 3200 bytes ebcdic made in MemSetHeader. And you can change it.         \
C09 See MemSetHeader.c: \"header\". If you had changed the source, you should     \
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
C25 Jiashun Yu's Team,                                                          \
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

int MemSetReelHead( bhed* re_h )
{

	int i, j;
	for( i=0; i<40; i++ )
	{
		for( j=0; j<80; j++ )
		{
			int index = i*80+j;
			re_h -> commend[index] = header[index];
		}
	}

	re_h->jobid = 1;
	re_h->lino  = 1;
	re_h->reno  = 1;
	re_h->ntrpr = 1;
	re_h->nart  = 1;
	re_h->hdt   = 0;
	re_h->dto   = 0;
	re_h->hns   = 0;
	re_h->nso   = 0;
	re_h->format= 5;
	re_h->fold  = 0;
	re_h->tsort = 0;
	re_h->vscode= 1;
	re_h->hsfs  = 0;
	re_h->hsfe  = 0;
	re_h->hslen = 0;
	re_h->hstyp = 0;
	re_h->schn  = 0;
	re_h->hstas = 0;
	re_h->hstae = 0;
	re_h->htatyp= 0;
	re_h->hcorr = 0;
	re_h->bgrcv = 0;
	re_h->rcvm  = 1;
	re_h->mfeet = 1;
	re_h->polyt = 0;
	re_h->vpol  = 0;

	for( i=0; i<170; i++ )
	{
		re_h->hunass[i] = 0;
	}

	return 0;
}

int MemSetTraceHead( segy* tr_h )
{
	tr_h->tracl = 1;
	tr_h->tracr = 1;
	tr_h->fldr  = 1;
	tr_h->tracf = 1;
	tr_h->ep    = 0;
	tr_h->cdp   = 0;
	tr_h->cdpt  = 0;
	tr_h->trid  = 1;
	tr_h->nvs   = 0;
	tr_h->nhs   = 0;
	tr_h->duse  = 1;
	tr_h->offset= 0;
	tr_h->gelev = 0;
	tr_h->selev = 0;
	tr_h->sdepth= 0;
	tr_h->gdel  = 0;
	tr_h->sdel  = 0;
	tr_h->swdep = 0;
	tr_h->gwdep = 0;
	tr_h->scalel= 0;
	tr_h->scalco= 0;
	tr_h->sx    = 0;
	tr_h->sy    = 0;
	tr_h->gx    = 0;
	tr_h->gy    = 0;
	tr_h->counit= 0;
	tr_h->wevel = 0;
	tr_h->swevel= 0;
	tr_h->sut   = 0;
	tr_h->gut   = 0;
	tr_h->sstat = 0;
	tr_h->gstat = 0;
	tr_h->tstat = 0;
	tr_h->laga  = 0;
	tr_h->lagb  = 0;
	tr_h->delrt = 0;
	tr_h->muts  = 0;
	tr_h->mute  = 0;
	tr_h->ns    = 1;
	tr_h->dt    = 1;
	tr_h->gain  = 0;
	tr_h->igc   = 0;
	tr_h->igi   = 0;
	tr_h->corr  = 0;
	tr_h->sfs   = 0;
	tr_h->sfe   = 0;
	tr_h->slen  = 0;
	tr_h->styp  = 0;
	tr_h->stas  = 0;
	tr_h->stae  = 0;
	tr_h->tatyp = 0;
	tr_h->afilf = 0;
	tr_h->afils = 0;
	tr_h->nofilf= 0;
	tr_h->nofils= 0;
	tr_h->lcf   = 0;
	tr_h->hcf   = 0;
	tr_h->lcs   = 0;
	tr_h->hcs   = 0;
	tr_h->year  = 0;
	tr_h->day   = 0;
	tr_h->hour  = 0;
	tr_h->minute= 0;
	tr_h->sec   = 0;
	tr_h->timbas= 0;
	tr_h->trwf  = 0;
	tr_h->grnors= 0;
	tr_h->grnofr= 0;
	tr_h->grnlof= 0;
	tr_h->gaps  = 0;
	tr_h->otrav = 0;
	tr_h->cdp_x = 0;
	tr_h->cdp_y = 0;
	tr_h->Inline= 0;
	tr_h->corssline = 0;
	tr_h->incident= 0;
	tr_h->shot = 0;
	tr_h->ffile = 0;
	tr_h->dimension=0;

	int i;
	for( i=0; i<14; i++ )
	{
		tr_h->unass[i] = 0;
	}

	return 0;
}
