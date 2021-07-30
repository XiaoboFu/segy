//=============================================
//Summary:
//          segy
//FileName:
//          segy.cpp
//Date:
//          2019/8/10
//Version:
//          1.0 (Windows)
//Author:
//          Xiaobo.Foo （xiaobo_foo@126.com）
//=============================================
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "segy.h"



/// <summary>	The header[ 3200]. </summary>
static char header[3200] = {"\
C01 This tape was made at the SEGY                                              \
C02                                                                             \
C03 This SEGY file module is a standard IEEE format.                            \
C04 All segy file format would be transform IEEE format.                        \
C05                                                                             \
C06 The segy lib made by Xiaobo Foo and Jianlong Yuan (CDUT).                   \
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
C27 ph.D: Jianlong Yuan, Guang Qian, Binghuang Qiu, Xiaobo Foo, Chao Han        \
C28 M.S: Xiaoping Hou, Xin Yi, Weizu Liu                                        \
C29                                                                             \
C30 Contact us: E mail: Xiaobo_foo@126.com                                      \
C31                 QQ: 649294261                                               \
C32              Phone: 15881053339                                             \
C33 Made this module at:2015.11.06                                              \
C34 Modify this module at: 2016.06.17                                           \
C35                                                                             \
C36                                                                             \
C37                                                                             \
C38                                                                             \
C39                                                                             \
C40 END EBCDIC                                                                 "
};

/// <summary>	Memory set reel head. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="re_h">	[in,out] If non-null, the re h. </param>

void MemSetReelHead(bhed* re_h)
{

	int i, j;
	for (i = 0; i<40; i++)
	{
		for (j = 0; j<80; j++)
		{
			int index = i * 80 + j;
			re_h->commend[index] = header[index];
		}
	}

	re_h->jobid = 1;
	re_h->lino = 1;
	re_h->reno = 1;
	re_h->ntrpr = 1;
	re_h->nart = 1;
	re_h->hdt = 0;
	re_h->dto = 0;
	re_h->hns = 0;
	re_h->nso = 0;
	re_h->format = 5;
	re_h->fold = 0;
	re_h->tsort = 0;
	re_h->vscode = 1;
	re_h->hsfs = 0;
	re_h->hsfe = 0;
	re_h->hslen = 0;
	re_h->hstyp = 0;
	re_h->schn = 0;
	re_h->hstas = 0;
	re_h->hstae = 0;
	re_h->htatyp = 0;
	re_h->hcorr = 0;
	re_h->bgrcv = 0;
	re_h->rcvm = 1;
	re_h->mfeet = 1;
	re_h->polyt = 0;
	re_h->vpol = 0;

	for (i = 0; i<170; i++)
	{
		re_h->hunass[i] = 0;
	}

	return;
}

/// <summary>	Memory set trace head. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="tr_h">	[in,out] If non-null, the tr h. </param>

void MemSetTraceHead(segy* tr_h)
{
	tr_h->tracl = 1;
	tr_h->tracr = 1;
	tr_h->fldr = 1;
	tr_h->tracf = 1;
	tr_h->ep = 0;
	tr_h->cdp = 0;
	tr_h->cdpt = 0;
	tr_h->trid = 1;
	tr_h->nvs = 0;
	tr_h->nhs = 0;
	tr_h->duse = 1;
	tr_h->offset = 0;
	tr_h->gelev = 0;
	tr_h->selev = 0;
	tr_h->sdepth = 0;
	tr_h->gdel = 0;
	tr_h->sdel = 0;
	tr_h->swdep = 0;
	tr_h->gwdep = 0;
	tr_h->scalel = 0;
	tr_h->scalco = 0;
	tr_h->sx = 0;
	tr_h->sy = 0;
	tr_h->gx = 0;
	tr_h->gy = 0;
	tr_h->counit = 0;
	tr_h->wevel = 0;
	tr_h->swevel = 0;
	tr_h->sut = 0;
	tr_h->gut = 0;
	tr_h->sstat = 0;
	tr_h->gstat = 0;
	tr_h->tstat = 0;
	tr_h->laga = 0;
	tr_h->lagb = 0;
	tr_h->delrt = 0;
	tr_h->muts = 0;
	tr_h->mute = 0;
	tr_h->ns = 1;
	tr_h->dt = 1;
	tr_h->gain = 0;
	tr_h->igc = 0;
	tr_h->igi = 0;
	tr_h->corr = 0;
	tr_h->sfs = 0;
	tr_h->sfe = 0;
	tr_h->slen = 0;
	tr_h->styp = 0;
	tr_h->stas = 0;
	tr_h->stae = 0;
	tr_h->tatyp = 0;
	tr_h->afilf = 0;
	tr_h->afils = 0;
	tr_h->nofilf = 0;
	tr_h->nofils = 0;
	tr_h->lcf = 0;
	tr_h->hcf = 0;
	tr_h->lcs = 0;
	tr_h->hcs = 0;
	tr_h->year = 0;
	tr_h->day = 0;
	tr_h->hour = 0;
	tr_h->minute = 0;
	tr_h->sec = 0;
	tr_h->timbas = 0;
	tr_h->trwf = 0;
	tr_h->grnors = 0;
	tr_h->grnofr = 0;
	tr_h->grnlof = 0;
	tr_h->gaps = 0;
	tr_h->otrav = 0;
	tr_h->cdp_x = 0;
	tr_h->cdp_y = 0;
	tr_h->Inline = 0;
	tr_h->corssline = 0;
	tr_h->incident = 0;
	tr_h->ntrac = 0;
	tr_h->ffile = 0;
	tr_h->dimension = 0;

	int i;
    for (i = 0; i<14; i++)
	{
		tr_h->unass[i] = 0;
	}

	return;
}

/// <summary>	Gets sgy information. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="ifile"> 	[in,out] If non-null, the ifile. </param>
/// <param name="re">	 	[in,out] If non-null, the re. </param>
/// <param name="ntrace">	[in,out] If non-null, the ntrace. </param>
/// <param name="ns">	 	[in,out] If non-null, the ns. </param>
/// <param name="dt">	 	[in,out] If non-null, the dt. </param>
///
/// <returns>	The sgy information. </returns>

int getSgyInfo(FILE *_File, bhed *re)
{
	// record current position
	//fseek(_File, SEEK_SET, SEEK_CUR);
	//long csize = ftell(_File);

#ifdef _WIN32
	_fseeki64(_File, SEEK_SET, SEEK_END);/* seek from the start to the end */
	__int64 fsize = _ftelli64(_File);	/* get the size of the segy file */
#else
    fseek(_File, SEEK_SET, SEEK_END);/* seek from the start to the end */
    long fsize = ftell(_File);	/* get the size of the segy file */

#endif
	rewind(_File);
	fread(re, 3600, 1, _File);


	if (re->format > 255)
	{
		swapbhed(re);
	}

	int ntrace = (int)((fsize - 3600) / (240 + sizeof(float)*(re->hns)));

	fseek(_File, 3600, SEEK_SET);

	return ntrace;
}

int getSgyInfochar(char *ifile, bhed *re, int *ntrace, int *ns, int *dt)
{

    FILE *ifp;

    long int fsize = 0;

    if ((ifp = fopen(ifile, "rb")) == NULL)
    {
        fprintf(stderr, "----------------------------------------------------------------\n");
        fprintf(stderr, " Sorry, open the %s file failed, when get segy info!\n", ifile);
        fprintf(stderr, "----------------------------------------------------------------\n");
        exit(0);
    }

    fseek(ifp, SEEK_SET, SEEK_END);/* seek from the start to the end */
    fsize = ftell(ifp);	/* get the size of the segy file */

    rewind(ifp);

    fread(re, 3600, 1, ifp);

    if (re->format > 255)
    {
        swapbhed(re);
    }

    int i, j;
    for (i = 0; i<40; i++)
    {
        for (j = 0; j<80; j++)
        {
            int index = i * 80 + j;
            re->commend[index] = header[index];
        }
    }

    //	fprintf(stderr,"Format = %d\n",re->format);

    re->format = 5;
    /* get the trace length */
    *ns = re->hns;
    /* get the traces of the seismic wave data */
    *ntrace = (fsize - 3600) / (240 + sizeof(float)*(*ns));

    *dt = re->hdt;

    fclose(ifp);

    return EXIT_SUCCESS;
}

/// <summary>	Segyreads the given file. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/10. </remarks>
///
/// <param name="file">  	[in,out] If non-null, the file. </param>
/// <param name="tr">	 	[in,out] If non-null, the tr. </param>
/// <param name="trace"> 	[in,out] If non-null, the trace. </param>
/// <param name="re">	 	The re. </param>
/// <param name="cTrace">	Current trace from 1. </param>
///
/// <returns>	An int. </returns>

int segyread(char *file, segy*tr, float*trace, bhed re, int cTrace)
{
	FILE *_File = NULL;
	_File = fopen(file, "rb");
	if (_File == NULL)
	{
		fprintf(stderr, "-------------------------------\n");
		fprintf(stderr, " Open file %s failed!\n", file);
		fprintf(stderr, "-------------------------------\n");

		return EXIT_FAILURE;
	}
	fseek(_File, 3600L + (240L + 4L * (long)re.hns) *(long)(cTrace-1), SEEK_SET);

	_segyread(_File, tr, trace, re);

	fclose(_File);

	return EXIT_SUCCESS;
}

/// <summary>	Segyreads. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/10. </remarks>
///
/// <param name="_File">	[in,out] If non-null, the file. </param>
/// <param name="tr">   	[in,out] If non-null, the tr. </param>
/// <param name="trace">	[in,out] If non-null, the trace. </param>
/// <param name="re">   	The re. </param>
///
/// <returns>	An int. </returns>

int _segyread(FILE *_File, segy *tr, float *trace, bhed re)
{
	fread(tr, 240, 1, _File);
	fread(trace, re.hns, sizeof(float), _File);

	if (re.format == 1)
	{
		swaphdrs(tr);	
		ibm_to_float((int *)trace, (int *)trace, re.hns, 0, 1);
	}

	return EXIT_SUCCESS;
}
//int segyread(char *ifile, segy *tr, float *trace, int cTrace)
//{
//	FILE *ifp = NULL;
//
//	bhed re;
//
//	int it = 0;
//	int ns = 0;
//	int ntrace = 0;
//	long fsize = 0;
//	int big = 0;
//
//	if ((ifp = fopen(ifile, "rb")) == NULL)
//	{
//		fprintf(stderr, "-----------------------------------------------------------------\n");
//		fprintf(stderr, " Open file: %s! Failed \n", ifile);
//		fprintf(stderr, "-----------------------------------------------------------------\n");
//		exit(0);
//	}
//
//	fread(&re, 3600, 1, ifp);
//
//	if (re.format > 255)
//	{
//		big = 1;
//		swapbhed(&re);
//	}
//	else
//	{
//		big = 0;
//	}
//
//	ns = re.hns;		/* get the trace length */
//
//	fseek(ifp, 0, 2);		/* seek from the start to the end */
//	fsize = ftell(ifp);		/* get the size of the segy file */
//
//	/* get the traces of the seismic wave data */
//	ntrace = (fsize - 3600) / (240 + sizeof(float)*ns);
//
//	if (cTrace > ntrace)
//	{
//		fprintf(stderr, "|----------------------------------------------|\n");
//		fprintf(stderr, "| Sorry, the segy is to end. Not enough trace. |\n");
//		fprintf(stderr, "|----------------------------------------------|\n");
//
//		return EXIT_FAILURE;
//	}
//
//	rewind(ifp);		/* file pointer return to the file start */
//
//	/* skip 3600 bytes from the file start */
//	fseek(ifp, 3600L + (240L + 4L * (long)ns) *(long)cTrace, 0);
//
//	/* read the segy traces head of 240 bytes */
//	fread(tr, 240, 1, ifp);
//	if (big)
//	{
//		swaphdrs(tr);
//	}
//
//	/* read the seismic data from the segy file */
//	fread(trace, sizeof(float)*ns, 1, ifp);
//
//	fclose(ifp);
//
//	if (re.format == 1)
//	{
//		ibm_to_float((int *)trace, (int *)trace, ns, !big, 0);
//		return EXIT_SUCCESS;
//	}
//	else if (big && re.format == 5)
//	{
//		for (it = 0; it < ns; it++)
//		{
//			swapbs((char*)(trace + it), 4);
//		}
//		return EXIT_SUCCESS;
//	}
//	else if (re.format == 2)
//	{
//		int_to_float((int *)trace, (float *)trace, ns, !big);
//	}
//	else if (re.format == 3)
//	{
//		short_to_float((short *)trace, (float *)trace, ns, !big);
//	}
//	else
//	{
//		return EXIT_SUCCESS;
//	}
//
//	return EXIT_SUCCESS;
//}

/// <summary>	Segywrites the given file. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/10. </remarks>
///
/// <param name="file">  	[in,out] If non-null, the file. </param>
/// <param name="re">	 	The re. </param>
/// <param name="tr">	 	The tr. </param>
/// <param name="trace"> 	[in,out] If non-null, the trace. </param>
/// <param name="format">	Describes the format to use. </param>
/// <param name="cTrace">	The trace. </param>
///
/// <returns>	An int. </returns>

int segywrite(char *file, bhed re, segy tr, float *trace, int format, int cTrace)
{
	FILE *_File = NULL;
	if (cTrace > 1)
	{
		_File = fopen(file, "ab");
	}
	else
	{
		_File = fopen(file, "wb");
	}
	
	_segywrite(_File, re, tr, trace, format, cTrace);

	fclose(_File);
	return EXIT_SUCCESS;
}

/// <summary>	Segywrites. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/10. </remarks>
///
/// <param name="_File"> 	[in,out] If non-null, the file. </param>
/// <param name="re">	 	The re. </param>
/// <param name="tr">	 	The tr. </param>
/// <param name="trace"> 	[in,out] If non-null, the trace. </param>
/// <param name="format">	Describes the format to use. </param>
/// <param name="cTrace">	The trace. </param>
///
/// <returns>	An int. </returns>

int _segywrite(FILE *_File, bhed re, segy tr, float *trace, int format, int cTrace)
{
	int ns = re.hns;
	int it;

	re.format = format;

	if (cTrace == 1)
	{
		if (re.format == 1)
		{
			swapbhed(&re);
		}

		fwrite(&re, sizeof(bhed), 1, _File);
	}

	if (format == 1)
	{
		swaphdrs(&tr);
		float_to_ibm((int*)trace, (int *)trace, ns, 1);
		for (it = 0; it < ns; it++)
		{
			swap_float_4(trace + it);
		}
	}

	fwrite(&tr, sizeof(segy), 1, _File);
	fwrite(trace, ns, sizeof(float), _File);
	
	return EXIT_SUCCESS;
}

//int segywrite(char *ofile, bhed re, segy tr, float *trace, int format, int cTrace)
//{
//	int it;
//	float *odata = NULL;
//	odata = (float *)malloc(tr.ns*sizeof(float));
//	for (it = 0; it < tr.ns; it++)
//	{
//		odata[it] = trace[it];
//	}
//
//	FILE *ofp;
//	int fsize = 0;
//
//	if ((ofp = fopen(ofile, "ab")) == NULL)
//	{
//		perror("Output oepn failed, when write segy file!\n");
//		exit(0);
//	}
//
//	fseek(ofp, SEEK_SET, SEEK_END);
//	fsize = ftell(ofp);
//
//	re.format = format;
//
//	if (fsize < 3600 || cTrace == 0)
//	{
//		fclose(ofp);
//		ofp = fopen(ofile, "wb");
//
//		if (re.format==1)
//		{
//			swapbhed(&re);
//		}
//
//		fwrite(&re, 3600, 1, ofp);
//	}
//
//	if (re.format == 1)
//	{
//		swaphdrs(&tr);
//
//		float_to_ibm((int*)odata, (int *)odata, tr.ns, 1);
//		for (it = 0; it < tr.ns; it++)
//		{
//			swap_float_4(odata + it);
//		}		
//	}
//
//	fwrite(&tr, 240, 1, ofp);
//	fwrite(odata, 4 * tr.ns, 1, ofp);
//
//	fclose(ofp);
//
//	free(odata);
//
//	return EXIT_SUCCESS;
//}

/// <summary>	Picks the CD pgather. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="file">	   	[in,out] If non-null, the file. </param>
/// <param name="trBuf">   	[in,out] If non-null, buffer for tr data. </param>
/// <param name="traceBuf">	[in,out] If non-null, buffer for trace data. </param>
/// <param name="size">	   	[in,out] If non-null, the size. </param>
/// <param name="ntr">	   	[in,out] If non-null, the ntr. </param>
/// <param name="flag">	   	[in,out] If non-null, the flag. </param>

void pickCDPgather(char *file, segy *trBuf, float *traceBuf, long int *size, int *ntr, int *flag)
{
	FILE *ifp = NULL;
	if ((ifp = fopen(file, "rb")) == NULL)
	{
		puts("\n");
		fprintf(stderr, "-----------------------------------------------------\n");
		fprintf(stderr, " Sorry, can't open the file of %s.\n", file);
		fprintf(stderr, "-----------------------------------------------------\n");
		puts("\n");
		exit(0);
	}

	bhed re;
	segy tr;
	int big;
	fread(&re, 3600, 1, ifp);
	bhed_convert(&re, &big);

	int ntrace = 0;
	int ns = 0;

	int fsize;
	fseek(ifp, SEEK_SET, SEEK_END);
	fsize = ftell(ifp);
	ns = re.hns;
	ntrace = (fsize - 3600) / (240 + 4 * ns);

	if (*size<3600)
	{
		*size = 3600L;
	}
	fseek(ifp, *size, SEEK_SET);

	float *trace = NULL; trace = (float *)malloc(4 * ns);

	int cdp = 0;
	int itr = 0;
	for (itr = 0; itr<ntrace; itr++)
	{
		fread(&tr, 240, 1, ifp);
		fread(trace, ns, 4, ifp);

		segy_convert(&tr, big);
		data_convert(trace, ns, big, re.format);

		if (itr == 0) cdp = tr.cdp;

		if (tr.cdp == cdp)
		{
			headCopy(trBuf, tr, itr);
			traceCopy(traceBuf, trace, ns, itr);
		}
		else
		{
			fseek(ifp, -4 * ns - 240, SEEK_CUR);
			*size = ftell(ifp);
			*flag = 0;
			*ntr = itr;
			break;
		}

		if (fsize == ftell(ifp))
		{
			*flag = 1;
			*ntr = itr + 1;
			break;
		}
	}

	free(trace);

	fclose(ifp);

	return;
}

/// <summary>	Picks the shotgather. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="ifile">   	[in,out] If non-null, the ifile. </param>
/// <param name="trBuf">   	[in,out] If non-null, buffer for tr data. </param>
/// <param name="traceBuf">	[in,out] If non-null, buffer for trace data. </param>
/// <param name="size">	   	[in,out] If non-null, the size. </param>
/// <param name="ntr">	   	[in,out] If non-null, the ntr. </param>
/// <param name="flag">	   	[in,out] If non-null, the flag. </param>

void pickShotgather(char *ifile, segy *trBuf, float *traceBuf, long int *size, int *ntr, int *flag)
{
	FILE *ifp;
	ifp = fopen(ifile, "rb");
	if (ifp == NULL)
	{
		fprintf(stderr, "|-----------------------------------------------------|\n");
		fprintf(stderr, "| Sorry, can't open the file of %s. |\n", ifile);
		fprintf(stderr, "|-----------------------------------------------------|\n");
		exit(0);
	}

	bhed re;
	segy tr;
	int big = 0;
	fread(&re, 3600, 1, ifp);
	bhed_convert(&re, &big);

	int ntrace = 0;
	int ns = 0;
	int fsize;

	fseek(ifp, SEEK_SET, SEEK_END);
	fsize = ftell(ifp);
	ns = re.hns;
	ntrace = (fsize - 3600) / (240 + 4 * ns);

	if (*size<3600)
	{
		*size = 3600L;
	}
	fseek(ifp, *size, SEEK_SET);

	float *trace = NULL; trace = (float *)malloc(4 * ns);

	int cep = -1;
	int itr = 0;
	for (itr = 0; itr<ntrace; itr++)
	{
		fread(&tr, 240, 1, ifp);
		fread(trace, ns, 4, ifp);

		segy_convert(&tr, big);
		data_convert(trace, ns, big, re.format);

		if (itr == 0)
		{
			cep = tr.ep;
		}

		if (tr.ep == cep)
		{
			headCopy(trBuf, tr, itr);
			traceCopy(traceBuf, trace, ns, itr);
		}
		else
		{
			fseek(ifp, -4 * ns - 240, SEEK_CUR);
			*size = ftell(ifp);
			*flag = 0;
			*ntr = itr;
			break;
		}

		if (fsize == ftell(ifp))
		{
			*flag = 1;
			*ntr = itr + 1;
			break;
		}
	}

	free(trace);
	fclose(ifp);

	return;
}

/// <summary>	Segy convert. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="tr_h">	[in,out] If non-null, the tr h. </param>
/// <param name="big"> 	The big. </param>

void segy_convert(segy *tr_h, int big)
{
	if (big)
	{
		swaphdrs(tr_h);
	}

	return;
}

/// <summary>	Swapbhed the given rh. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="rh">	[in,out] If non-null, the rh. </param>

void swapbhed(bhed *rh)
{
	int ix; ix = 0;
	swapbs((char *)&(*rh).jobid, 4);
	swapbs((char *)&(*rh).lino, 4);
	swapbs((char *)&(*rh).reno, 4);
	swapbs((char *)&(*rh).ntrpr, 2);
	swapbs((char *)&(*rh).nart, 2);
	swapbs((char *)&(*rh).hdt, 2);
	swapbs((char *)&(*rh).dto, 2);
	swapbs((char *)&(*rh).hns, 2);
	swapbs((char *)&(*rh).nso, 2);
	swapbs((char *)&(*rh).format, 2);
	swapbs((char *)&(*rh).fold, 2);
	swapbs((char *)&(*rh).tsort, 2);
	swapbs((char *)&(*rh).vscode, 2);
	swapbs((char *)&(*rh).hsfs, 2);
	swapbs((char *)&(*rh).hsfe, 2);
	swapbs((char *)&(*rh).hslen, 2);
	swapbs((char *)&(*rh).hstyp, 2);
	swapbs((char *)&(*rh).schn, 2);
	swapbs((char *)&(*rh).hstas, 2);
	swapbs((char *)&(*rh).hstae, 2);
	swapbs((char *)&(*rh).htatyp, 2);
	swapbs((char *)&(*rh).hcorr, 2);
	swapbs((char *)&(*rh).bgrcv, 2);
	swapbs((char *)&(*rh).rcvm, 2);
	swapbs((char *)&(*rh).mfeet, 2);
	swapbs((char *)&(*rh).polyt, 2);
	swapbs((char *)&(*rh).vpol, 2);
	for (ix = 0; ix<170; ix++)
		swapbs((char *)((*rh).hunass + ix), 2);
}

/// <summary>	Swaphdrs the given hdrs. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="hdrs">	[in,out] If non-null, the hdrs. </param>

void swaphdrs(segy *hdrs)
{
	int ix; ix = 0;
	swapbs((char *)&(*hdrs).tracl, 4);
	swapbs((char *)&(*hdrs).tracr, 4);
	swapbs((char *)&(*hdrs).fldr, 4);
	swapbs((char *)&(*hdrs).tracf, 4);
	swapbs((char *)&(*hdrs).ep, 4);
	swapbs((char *)&(*hdrs).cdp, 4);
	swapbs((char *)&(*hdrs).cdpt, 4);
	swapbs((char *)&(*hdrs).trid, 4);
	swapbs((char *)&(*hdrs).nvs, 2);
	swapbs((char *)&(*hdrs).nhs, 2);
	swapbs((char *)&(*hdrs).duse, 2);
	swapbs((char *)&(*hdrs).offset, 4);
	swapbs((char *)&(*hdrs).gelev, 4);
	swapbs((char *)&(*hdrs).selev, 4);
	swapbs((char *)&(*hdrs).sdepth, 4);
	swapbs((char *)&(*hdrs).gdel, 4);
	swapbs((char *)&(*hdrs).sdel, 4);
	swapbs((char *)&(*hdrs).swdep, 4);
	swapbs((char *)&(*hdrs).gwdep, 4);
	swapbs((char *)&(*hdrs).scalel, 2);
	swapbs((char *)&(*hdrs).scalco, 2);
	swapbs((char *)&(*hdrs).sx, 4);
	swapbs((char *)&(*hdrs).sy, 4);
	swapbs((char *)&(*hdrs).gx, 4);
	swapbs((char *)&(*hdrs).gy, 4);
	swapbs((char *)&(*hdrs).counit, 2);
	swapbs((char *)&(*hdrs).wevel, 2);
	swapbs((char *)&(*hdrs).swevel, 2);
	swapbs((char *)&(*hdrs).sut, 2);
	swapbs((char *)&(*hdrs).gut, 2);
	swapbs((char *)&(*hdrs).sstat, 2);
	swapbs((char *)&(*hdrs).gstat, 2);
	swapbs((char *)&(*hdrs).tstat, 2);
	swapbs((char *)&(*hdrs).laga, 2);
	swapbs((char *)&(*hdrs).lagb, 2);
	swapbs((char *)&(*hdrs).delrt, 2);
	swapbs((char *)&(*hdrs).muts, 2);
	swapbs((char *)&(*hdrs).mute, 2);
	swapbs((char *)&(*hdrs).ns, 2);
	swapbs((char *)&(*hdrs).dt, 2);
	swapbs((char *)&(*hdrs).gain, 2);
	swapbs((char *)&(*hdrs).igc, 2);
	swapbs((char *)&(*hdrs).igi, 2);
	swapbs((char *)&(*hdrs).corr, 2);
	swapbs((char *)&(*hdrs).sfs, 2);
	swapbs((char *)&(*hdrs).sfe, 2);
	swapbs((char *)&(*hdrs).slen, 2);
	swapbs((char *)&(*hdrs).styp, 2);
	swapbs((char *)&(*hdrs).stas, 2);
	swapbs((char *)&(*hdrs).stae, 2);
	swapbs((char *)&(*hdrs).tatyp, 2);
	swapbs((char *)&(*hdrs).afilf, 2);
	swapbs((char *)&(*hdrs).afils, 2);
	swapbs((char *)&(*hdrs).nofilf, 2);
	swapbs((char *)&(*hdrs).nofils, 2);
	swapbs((char *)&(*hdrs).lcf, 2);
	swapbs((char *)&(*hdrs).hcf, 2);
	swapbs((char *)&(*hdrs).lcs, 2);
	swapbs((char *)&(*hdrs).hcs, 2);
	swapbs((char *)&(*hdrs).year, 2);
	swapbs((char *)&(*hdrs).day, 2);
	swapbs((char *)&(*hdrs).hour, 2);
	swapbs((char *)&(*hdrs).minute, 2);
	swapbs((char *)&(*hdrs).sec, 2);
	swapbs((char *)&(*hdrs).timbas, 2);
	swapbs((char *)&(*hdrs).trwf, 2);
	swapbs((char *)&(*hdrs).grnors, 2);
	swapbs((char *)&(*hdrs).grnofr, 2);
	swapbs((char *)&(*hdrs).grnlof, 2);
	swapbs((char *)&(*hdrs).gaps, 2);
	swapbs((char *)&(*hdrs).otrav, 2);
    swapbs((char *)&(*hdrs).cdp_x, 4);
    swapbs((char *)&(*hdrs).cdp_y, 4);
    swapbs((char *)&(*hdrs).Inline, 4);
    swapbs((char *)&(*hdrs).corssline, 4);
    swapbs((char *)&(*hdrs).incident, 4);
    swapbs((char *)&(*hdrs).ntrac, 4);
    swapbs((char *)&(*hdrs).ffile, 4);
    swapbs((char *)&(*hdrs).dimension, 4);

    for (ix = 0; ix<14; ix++)
		swapbs((char *)((*hdrs).unass + ix), 2);

}

/// <summary>	Swapbs. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="buf"> 	[in,out] If non-null, the buffer. </param>
/// <param name="size">	The size. </param>

void swapbs(char *buf, short size){
	char tmp;
	switch (size){
	case 2:
		tmp = buf[0]; buf[0] = buf[1]; buf[1] = tmp;
		break;
	case 4:
		tmp = buf[0]; buf[0] = buf[3]; buf[3] = tmp;
		tmp = buf[1]; buf[1] = buf[2]; buf[2] = tmp;
		break;
	case 8:
		tmp = buf[0]; buf[0] = buf[7]; buf[7] = tmp;
		tmp = buf[1]; buf[1] = buf[6]; buf[6] = tmp;
		tmp = buf[2]; buf[2] = buf[5]; buf[5] = tmp;
		tmp = buf[3]; buf[3] = buf[4]; buf[4] = tmp;
		break;
	default:
		break;
	}
}

/// <summary>	Swap short 2. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni2">	[in,out] If non-null, the second tni. </param>

void swap_short_2(short *tni2)
{
	*tni2 = (((*tni2 >> 8) & 0xff) | ((*tni2 & 0xff) << 8));
}

/// <summary>	Swap u short 2. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni2">	[in,out] If non-null, the second tni. </param>

void swap_u_short_2(unsigned short *tni2)
{
	*tni2 = (((*tni2 >> 8) & 0xff) | ((*tni2 & 0xff) << 8));
}

/// <summary>	Swap int 4. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni4">	[in,out] If non-null, the fourth tni. </param>

void swap_int_4(int *tni4)
{
	*tni4 = (((*tni4 >> 24) & 0xff) | ((*tni4 & 0xff) << 24) |
		((*tni4 >> 8) & 0xff00) | ((*tni4 & 0xff00) << 8));
}

/// <summary>	Swap u int 4. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni4">	[in,out] If non-null, the fourth tni. </param>

void swap_u_int_4(unsigned int *tni4)
{
	*tni4 = (((*tni4 >> 24) & 0xff) | ((*tni4 & 0xff) << 24) |
		((*tni4 >> 8) & 0xff00) | ((*tni4 & 0xff00) << 8));
}

/// <summary>	Swap long 4. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni4">	[in,out] If non-null, the fourth tni. </param>

void swap_long_4(long *tni4)
{
	*tni4 = (((*tni4 >> 24) & 0xff) | ((*tni4 & 0xff) << 24) |
		((*tni4 >> 8) & 0xff00) | ((*tni4 & 0xff00) << 8));
}

/// <summary>	Swap u long 4. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tni4">	[in,out] If non-null, the fourth tni. </param>

void swap_u_long_4(unsigned long *tni4)
{
	*tni4 = (((*tni4 >> 24) & 0xff) | ((*tni4 & 0xff) << 24) |
		((*tni4 >> 8) & 0xff00) | ((*tni4 & 0xff00) << 8));
}

/// <summary>	Swap float 4. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tnf4">	[in,out] If non-null, the fourth tnf. </param>

void swap_float_4(float *tnf4)
{
	int *tni4 = (int *)tnf4;
	*tni4 = (((*tni4 >> 24) & 0xff) | ((*tni4 & 0xff) << 24) |
		((*tni4 >> 8) & 0xff00) | ((*tni4 & 0xff00) << 8));
}

/// <summary>	Swap double 8. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="tndd8">	[in,out] If non-null, the tndd 8. </param>

void swap_double_8(double *tndd8)
{
	char *tnd8 = (char *)tndd8;
	char tnc;

	tnc = *tnd8;
	*tnd8 = *(tnd8 + 7);
	*(tnd8 + 7) = tnc;

	tnc = *(tnd8 + 1);
	*(tnd8 + 1) = *(tnd8 + 6);
	*(tnd8 + 6) = tnc;

	tnc = *(tnd8 + 2);
	*(tnd8 + 2) = *(tnd8 + 5);
	*(tnd8 + 5) = tnc;

	tnc = *(tnd8 + 3);
	*(tnd8 + 3) = *(tnd8 + 4);
	*(tnd8 + 4) = tnc;
}

/// <summary>	Bhed convert. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="re_h">	[in,out] If non-null, the re h. </param>
/// <param name="big"> 	[in,out] If non-null, the big. </param>

void bhed_convert(bhed *re_h, int *big)
{
	if (re_h->format > 255)
	{
		*big = 1;
		swapbhed(re_h);
	}
	else
	{
		*big = 0;
	}

	return;
}

/// <summary>	Data convert. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="seis_data">	[in,out] If non-null, information describing the seis. </param>
/// <param name="tr_len">   	Length of the tr. </param>
/// <param name="big">			The big. </param>
/// <param name="format">   	Describes the format to use. </param>

void data_convert(float *seis_data, int tr_len, int big, int format)
{
	int it;

	if (big && format == 1)
	{
		ibm_to_float((int *)seis_data, (int *)seis_data, tr_len, 0, 0);
	}
	if (big && format == 5)
	{
		for (it = 0; it < tr_len; it++)
		{
			swapbs((char*)(seis_data + it), 4);
		}
	}

	return;
}

/// <summary>	Head copy. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="targ">	[in,out] If non-null, the targ. </param>
/// <param name="from">	Source for the. </param>
/// <param name="id">  	The identifier. </param>

void headCopy(segy *targ, segy from, int id)
{
	targ[id] = from;

	return;
}

// Copy the trace data to the trace buffer

/// <summary>	Trace copy. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="targ">	[in,out] If non-null, the targ. </param>
/// <param name="from">	[in,out] If non-null, source for the. </param>
/// <param name="size">	The size. </param>
/// <param name="id">  	The identifier. </param>

void traceCopy(float *targ, float *from, int size, int id)
{
	int i;
	for (i = 0; i<size; i++)
	{
		targ[id*size + i] = from[i];
	}

	return;
}

/**********************************************************************
*  float_to_ibm - convert between 32 bit IBM and IEEE floating numbers
***********************************************************************
*  Input:
*  from       input vector
*  n          number of floats in vectors
*  endian     =0 for little endian machine, =1 for big endian machines
*
*  Output:
*  to         output vector, can be same as input vector
*
***********************************************************************
*  Notes:
*  Up to 3 bits lost on IEEE -> IBM
*
*  IBM -> IEEE may overflow or underflow, taken care of by
*  substituting large number or zero
*
*  Only integer shifting and masking are used.
***********************************************************************
*  Credits:     CWP: Brian Sumner
***********************************************************************/

/// <summary>	Float to ibm. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="from">  	Source for the. </param>
/// <param name="to">	 	to. </param>
/// <param name="n">	 	An int to process. </param>
/// <param name="endian">	The endian. </param>

void float_to_ibm(int from[], int to[], int n, int endian)
{
	register int fconv, fmant, i, t;

	for (i = 0; i<n; ++i)
	{
		fconv = from[i];
		if (fconv)
		{
			fmant = (0x007fffff & fconv) | 0x00800000;
			t = (int)((0x7f800000 & fconv) >> 23) - 126;
			while (t & 0x3)
			{
				++t;
				fmant >>= 1;
			}

			fconv = (0x80000000 & fconv) | (((t >> 2) + 64) << 24) | fmant;
		}
		if (endian == 0)
			fconv = (fconv << 24) | ((fconv >> 24) & 0xff) |
			((fconv & 0xff00) << 8) | ((fconv & 0xff0000) >> 8);
		to[i] = fconv;
	}
	return;
}

/***********************************************************************
* ibm_to_float - convert between 32 bit IBM and IEEE floating numbers
* ************************************************************************
* Input::
* from		input vector
* to		output vector, can be same as input vector
* endian		byte order =0 little endian (DEC, PC's)
* 			    =1 other systems
* 			    *************************************************************************
* 			    Notes:
* 			    Up to 3 bits lost on IEEE -> IBM
*
* 			    Assumes sizeof(int) == 4
*
* 			    IBM -> IEEE may overflow or underflow, taken care of by
* 			    substituting large number or zero
*
* 			    Only integer shifting and masking are used.
* 			    *************************************************************************
* 			    Credits: CWP: Brian Sumner,  c.1985
* 			    *************************************************************************/

/// <summary>	Ibm to float. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="from">   	Source for the. </param>
/// <param name="to">	  	to. </param>
/// <param name="n">	  	An int to process. </param>
/// <param name="endian"> 	The endian. </param>
/// <param name="verbose">	The verbose. </param>

void ibm_to_float(int from[], int to[], int n, int endian, int verbose)
{
	register int fconv, fmant, i, t;
	for (i = 0; i < n; ++i) {
		fconv = from[i];
		/* if little endian, i.e. endian=0 do this */
		if (endian == 0) fconv = (fconv << 24) | ((fconv >> 24) & 0xff) |
			((fconv & 0xff00) << 8) | ((fconv & 0xff0000) >> 8);
		if (fconv) {
			fmant = 0x00ffffff & fconv;
			/* The next two lines were added by Toralf Foerster */
			/* to trap non-IBM format data i.e. conv=0 data  */
			if (fmant == 0) {
				if (verbose == 2){
					printf("mantissa is zero data may not be in IBM FLOAT Format !");
					printf("setting fconv=0");
				}
				fconv = 0;
			}
			else {
				t = (int)((0x7f000000 & fconv) >> 22) - 130;
				while (!(fmant & 0x00800000)) {
					--t; fmant <<= 1;
				}
				if (t > 254)
					fconv = (0x80000000 & fconv) | 0x7f7fffff;
				else if (t <= 0)
					fconv = 0;
				else
					fconv = (0x80000000 & fconv) | (t << 23) | (0x007fffff & fmant);
			}
		}
		to[i] = fconv;
	}
}

/****************************************************************************
* short_to_float - type conversion for additional SEG-Y formats
* *****************************************************************************
* Author: Delft: J.W. de Bruijn, May 1995
* Modified by: Baltic Sea Reasearch Institute: Toralf Foerster, March 1997
* ****************************************************************************/

/// <summary>	Short to float. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="from">  	Source for the. </param>
/// <param name="to">	 	to. </param>
/// <param name="n">	 	An int to process. </param>
/// <param name="endian">	The endian. </param>

void short_to_float(short from[], float to[], int n, int endian)
{
	register int i;

	if (endian == 0) {
		for (i = n - 1; i >= 0; --i) {
			swap_short_2(&from[i]);
			to[i] = (float)from[i];
		}
	}
	else {
		for (i = n - 1; i >= 0; --i)
			to[i] = (float)from[i];
	}
}

/****************************************************************************
* integer1_to_float - type conversion for additional SEG-Y formats
* *****************************************************************************
* Author: John Stockwell,  2005
* ****************************************************************************/

/// <summary>	Integer 1 to float. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="from">	Source for the. </param>
/// <param name="to">  	to. </param>
/// <param name="n">   	An int to process. </param>

void integer1_to_float(signed char from[], float to[], int n)
{
	while (n--) {
		to[n] = from[n];
	}
}

/****************************************************************************
* Author: J.W. de Bruijn, May 1995
* ****************************************************************************/

/// <summary>	Int to float. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="from">  	Source for the. </param>
/// <param name="to">	 	to. </param>
/// <param name="n">	 	An int to process. </param>
/// <param name="endian">	The endian. </param>

void int_to_float(int from[], float to[], int n, int endian)
{
	register int i;

	if (endian == 0) {
		for (i = 0; i < n; ++i) {
			swap_int_4(&from[i]);
			to[i] = (float)from[i];
		}
	}
	else {
		for (i = 0; i < n; ++i) {
			to[i] = (float)from[i];
		}
	}
}

// Judge current trace is last trace of gather or not

/// <summary>	Last gather. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="p_cdp">	The cdp. </param>
/// <param name="n_cdp">	The cdp. </param>
///
/// <returns>	An int. </returns>

int LastGather(int p_cdp, int n_cdp)
{
	if (p_cdp == n_cdp)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// Judge current trace is last trace in the segy file or not

/// <summary>	Last trace. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/7. </remarks>
///
/// <param name="c_trace">	The trace. </param>
/// <param name="ntrace"> 	The ntrace. </param>
///
/// <returns>	An int. </returns>

int LastTrace(int c_trace, int ntrace)
{
	if (c_trace != ntrace)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/// <summary>	Writes a 2asc. </summary>
///
/// <remarks>	Xiaobo Fu, 2019/8/6. </remarks>
///
/// <param name="ou_file">  	[in,out] If non-null, the ou file. </param>
/// <param name="re_h">			The re h. </param>
/// <param name="tr_h">			The tr h. </param>
/// <param name="seis_data">	[in,out] If non-null, information describing the seis. </param>
/// <param name="cTrace">   	The trace. </param>

void write2asc(char *ou_file, bhed re_h, segy tr_h, float *seis_data, int cTrace)
{
	int ix = 0;
	FILE *ofp;
	if ((ofp = fopen(ou_file, "a+")) == NULL)
	{
		perror("Output oepn failed!\n");
		exit(0);
	}

	if (cTrace == 0)
	{
		fclose(ofp);
		ofp = fopen(ou_file, "w");

		for (ix = 0; ix<3200; ix++)
			fprintf(ofp, "%c ", re_h.commend[ix]);
		fprintf(ofp, "\n\n");
		fprintf(ofp, "%d %d %d ", re_h.jobid, re_h.lino, re_h.reno);
		fprintf(ofp, "%d %d %d ", re_h.ntrpr, re_h.nart, re_h.hdt);
		fprintf(ofp, "%d %d %d ", re_h.dto, re_h.hns, re_h.nso);
		fprintf(ofp, "%d %d %d ", re_h.format, re_h.fold, re_h.tsort);
		fprintf(ofp, "%d %d %d ", re_h.vscode, re_h.hsfs, re_h.hsfe);
		fprintf(ofp, "%d %d %d ", re_h.hslen, re_h.hstyp, re_h.schn);
		fprintf(ofp, "%d %d %d ", re_h.hstas, re_h.hstae, re_h.htatyp);
		fprintf(ofp, "%d %d %d ", re_h.hcorr, re_h.bgrcv, re_h.rcvm);
		fprintf(ofp, "%d %d %d ", re_h.mfeet, re_h.polyt, re_h.vpol);
		for (ix = 0; ix<85; ix++)
			fprintf(ofp, "%d ", re_h.hunass[ix]);
		fprintf(ofp, "\n\n");
	}

	fprintf(ofp, "%d %d %d %d %d ", tr_h.tracl, tr_h.tracr, tr_h.fldr, tr_h.tracf, tr_h.ep);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.cdp, tr_h.cdpt, tr_h.trid, tr_h.nvs, tr_h.nhs);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.duse, tr_h.offset, tr_h.gelev, tr_h.selev, tr_h.sdepth);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.gdel, tr_h.sdel, tr_h.swdep, tr_h.gwdep, tr_h.scalel);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.scalco, tr_h.sx, tr_h.sy, tr_h.gx, tr_h.gy);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.counit, tr_h.wevel, tr_h.swevel, tr_h.sut, tr_h.gut);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.sstat, tr_h.gstat, tr_h.tstat, tr_h.laga, tr_h.lagb);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.delrt, tr_h.muts, tr_h.mute, tr_h.ns, tr_h.dt);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.gain, tr_h.igc, tr_h.igi, tr_h.corr, tr_h.sfs);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.sfe, tr_h.slen, tr_h.styp, tr_h.stas, tr_h.stae);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.tatyp, tr_h.afilf, tr_h.afils, tr_h.nofilf, tr_h.nofils);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.lcf, tr_h.hcf, tr_h.lcs, tr_h.hcs, tr_h.year);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.day, tr_h.hour, tr_h.minute, tr_h.sec, tr_h.timbas);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.trwf, tr_h.grnors, tr_h.grnofr, tr_h.grnlof, tr_h.gaps);
	fprintf(ofp, "%d %d %d %d %d ", tr_h.otrav, tr_h.cdp_x, tr_h.cdp_y, tr_h.Inline, tr_h.corssline);
	fprintf(ofp, "%d ", tr_h.incident);
    for (ix = 0; ix<14; ix++)
		fprintf(ofp, "%d ", tr_h.unass[ix]);
	fprintf(ofp, "\n");

	for (ix = 0; ix<re_h.hns; ix++)
		fprintf(ofp, "%f\n", seis_data[ix]);

	fclose(ofp);
}
