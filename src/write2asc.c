#include <stdio.h>
#include <stdlib.h>

#include "segy.h"

int write2asc(const char *ou_file, bhed re_h, segy tr_h, float *seis_data, int cTrace )
{
	int ix = 0;
	int iy = 0;
	int id = 0;

	FILE *ofp;
	if((ofp = fopen(ou_file,"a+"))==NULL)
	{
		perror("Output oepn failed!\n");
		exit(0);
	}

	if(cTrace == 0)
	{
		fclose( ofp );
		ofp = fopen( ou_file, "w" );
		
		for( ix=0; ix<40; ix++ )
		{
			for(iy=0; iy<80; iy++)
			{
				id = ix * 80 + iy;
				fprintf( ofp, "%c ",re_h.commend[id]);
			}
		}
		fprintf(ofp,"\n\n");
		fprintf(ofp,"%d %d %d ",re_h.jobid, re_h.lino, re_h.reno);
		fprintf(ofp,"%d %d %d ",re_h.ntrpr, re_h.nart, re_h.hdt);
		fprintf(ofp,"%d %d %d ",re_h.dto,   re_h.hns,  re_h.nso);
		fprintf(ofp,"%d %d %d ",re_h.format,re_h.fold, re_h.tsort);
		fprintf(ofp,"%d %d %d ",re_h.vscode,re_h.hsfs, re_h.hsfe);
		fprintf(ofp,"%d %d %d ",re_h.hslen, re_h.hstyp,re_h.schn);
		fprintf(ofp,"%d %d %d ",re_h.hstas, re_h.hstae,re_h.htatyp);
		fprintf(ofp,"%d %d %d ",re_h.hcorr, re_h.bgrcv,re_h.rcvm);
		fprintf(ofp,"%d %d %d ",re_h.mfeet, re_h.polyt,re_h.vpol);
		for( ix=0; ix<85; ix++ )
			fprintf(ofp, "%d ", re_h.hunass[ix]);
		fprintf( ofp, "\n\n");
	}

	fprintf( ofp,"%d %d %d %d %d ",tr_h.tracl,  tr_h.tracr, tr_h.fldr,  tr_h.tracf, tr_h.ep);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.cdp,    tr_h.cdpt,  tr_h.trid,  tr_h.nvs,   tr_h.nhs);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.duse,   tr_h.offset,tr_h.gelev, tr_h.selev, tr_h.sdepth);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.gdel,   tr_h.sdel,  tr_h.swdep, tr_h.gwdep, tr_h.scalel);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.scalco, tr_h.sx,    tr_h.sy,    tr_h.gx,    tr_h.gy);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.counit, tr_h.wevel, tr_h.swevel,tr_h.sut,   tr_h.gut);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.sstat,  tr_h.gstat, tr_h.tstat, tr_h.laga,  tr_h.lagb);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.delrt,  tr_h.muts,  tr_h.mute,  tr_h.ns,    tr_h.dt);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.gain,   tr_h.igc,   tr_h.igi,   tr_h.corr,  tr_h.sfs);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.sfe,    tr_h.slen,  tr_h.styp,  tr_h.stas,  tr_h.stae);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.tatyp,  tr_h.afilf, tr_h.afils, tr_h.nofilf,tr_h.nofils);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.lcf,    tr_h.hcf,   tr_h.lcs,   tr_h.hcs,   tr_h.year);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.day,    tr_h.hour,  tr_h.minute,tr_h.sec,   tr_h.timbas);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.trwf,   tr_h.grnors,tr_h.grnofr,tr_h.grnlof,tr_h.gaps);
	fprintf( ofp,"%d %d %d %d %d ",tr_h.otrav,  tr_h.cdp_x, tr_h.cdp_y, tr_h.Inline,tr_h.corssline);
	fprintf( ofp,"%d ",   tr_h.incident);
	for( ix=0; ix<25; ix++ )
	{
		fprintf(ofp, "%d ", tr_h.unass[ix]);
	}
	fprintf( ofp,"\n");
	
	for( ix=0; ix<re_h.hns; ix++ )
	{
		fprintf(ofp,"%f\n",seis_data[ix]);
	}
		
	fclose(ofp);

	return 0;
}


int write2ascF(bhed re_h, segy tr_h, float *seis_data, int cTrace )
{
	int ix = 0;
	int iy = 0;
	int id = 0;

	if(stdout==NULL)
	{
		perror("Output oepn failed!\n");
		exit(0);
	}

	if(cTrace == 0)
	{
		for( ix=0; ix<40; ix++ )
		{
			for(iy=0; iy<80; iy++)
			{
				id = ix * 80 + iy;
				fprintf( stdout, "%c ",re_h.commend[id]);
			}
		}
		fprintf(stdout,"\n\n");
		fprintf(stdout,"%d %d %d ",re_h.jobid, re_h.lino, re_h.reno);
		fprintf(stdout,"%d %d %d ",re_h.ntrpr, re_h.nart, re_h.hdt);
		fprintf(stdout,"%d %d %d ",re_h.dto,   re_h.hns,  re_h.nso);
		fprintf(stdout,"%d %d %d ",re_h.format,re_h.fold, re_h.tsort);
		fprintf(stdout,"%d %d %d ",re_h.vscode,re_h.hsfs, re_h.hsfe);
		fprintf(stdout,"%d %d %d ",re_h.hslen, re_h.hstyp,re_h.schn);
		fprintf(stdout,"%d %d %d ",re_h.hstas, re_h.hstae,re_h.htatyp);
		fprintf(stdout,"%d %d %d ",re_h.hcorr, re_h.bgrcv,re_h.rcvm);
		fprintf(stdout,"%d %d %d ",re_h.mfeet, re_h.polyt,re_h.vpol);
		for( ix=0; ix<85; ix++ )
		{
			fprintf(stdout, "%d ", re_h.hunass[ix]);
		}
		fprintf( stdout, "\n\n");
	}

	fprintf( stdout,"%d %d %d %d %d ",tr_h.tracl,  tr_h.tracr, tr_h.fldr,  tr_h.tracf, tr_h.ep);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.cdp,    tr_h.cdpt,  tr_h.trid,  tr_h.nvs,   tr_h.nhs);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.duse,   tr_h.offset,tr_h.gelev, tr_h.selev, tr_h.sdepth);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.gdel,   tr_h.sdel,  tr_h.swdep, tr_h.gwdep, tr_h.scalel);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.scalco, tr_h.sx,    tr_h.sy,    tr_h.gx,    tr_h.gy);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.counit, tr_h.wevel, tr_h.swevel,tr_h.sut,   tr_h.gut);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.sstat,  tr_h.gstat, tr_h.tstat, tr_h.laga,  tr_h.lagb);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.delrt,  tr_h.muts,  tr_h.mute,  tr_h.ns,    tr_h.dt);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.gain,   tr_h.igc,   tr_h.igi,   tr_h.corr,  tr_h.sfs);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.sfe,    tr_h.slen,  tr_h.styp,  tr_h.stas,  tr_h.stae);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.tatyp,  tr_h.afilf, tr_h.afils, tr_h.nofilf,tr_h.nofils);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.lcf,    tr_h.hcf,   tr_h.lcs,   tr_h.hcs,   tr_h.year);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.day,    tr_h.hour,  tr_h.minute,tr_h.sec,   tr_h.timbas);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.trwf,   tr_h.grnors,tr_h.grnofr,tr_h.grnlof,tr_h.gaps);
	fprintf( stdout,"%d %d %d %d %d ",tr_h.otrav,  tr_h.cdp_x, tr_h.cdp_y, tr_h.Inline,tr_h.corssline);
	fprintf( stdout,"%d ",   tr_h.incident);
	for( ix=0; ix<25; ix++ )
	{
		fprintf(stdout, "%d ", tr_h.unass[ix]);
	}
	fprintf( stdout,"\n");
	
	for( ix=0; ix<tr_h.ns; ix++ )
	{
		fprintf(stdout,"%f\n",seis_data[ix]);
	}

	return 0;
}
