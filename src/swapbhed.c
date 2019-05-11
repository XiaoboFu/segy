
#include "segy.h"

void swapbhed( bhed *rh)
{
	int ix; ix = 0;
	swapbs( (char *)&(*rh).jobid , 4 );
	swapbs( (char *)&(*rh).lino  , 4 );
	swapbs( (char *)&(*rh).reno  , 4 );
	swapbs( (char *)&(*rh).ntrpr , 2 );
	swapbs( (char *)&(*rh).nart  , 2 );
	swapbs( (char *)&(*rh).hdt   , 2 );
	swapbs( (char *)&(*rh).dto   , 2 );
	swapbs( (char *)&(*rh).hns   , 2 );
	swapbs( (char *)&(*rh).nso   , 2 );
	swapbs( (char *)&(*rh).format, 2 );
	swapbs( (char *)&(*rh).fold  , 2 );
	swapbs( (char *)&(*rh).tsort , 2 );
	swapbs( (char *)&(*rh).vscode, 2 );
	swapbs( (char *)&(*rh).hsfs  , 2 );
	swapbs( (char *)&(*rh).hsfe  , 2 );
	swapbs( (char *)&(*rh).hslen , 2 );
	swapbs( (char *)&(*rh).hstyp , 2 );
	swapbs( (char *)&(*rh).schn  , 2 );
	swapbs( (char *)&(*rh).hstas , 2 );
	swapbs( (char *)&(*rh).hstae , 2 );
	swapbs( (char *)&(*rh).htatyp, 2 );
	swapbs( (char *)&(*rh).hcorr , 2 );
	swapbs( (char *)&(*rh).bgrcv , 2 );
	swapbs( (char *)&(*rh).rcvm  , 2 );
	swapbs( (char *)&(*rh).mfeet , 2 );
	swapbs( (char *)&(*rh).polyt , 2 );
	swapbs( (char *)&(*rh).vpol  , 2 );
	for( ix=0; ix<170; ix++ )
		swapbs( (char *)((*rh).hunass+ix) , 2 );
}

void swaphdrs( segy *hdrs)
{
	int ix; ix = 0;
	swapbs( (char *)&(*hdrs).tracl    , 4 );
	swapbs( (char *)&(*hdrs).tracr    , 4 );
	swapbs( (char *)&(*hdrs).fldr     , 4 );
	swapbs( (char *)&(*hdrs).tracf    , 4 );
	swapbs( (char *)&(*hdrs).ep       , 4 );
	swapbs( (char *)&(*hdrs).cdp      , 4 );
	swapbs( (char *)&(*hdrs).cdpt     , 4 );
	swapbs( (char *)&(*hdrs).trid     , 4 );
	swapbs( (char *)&(*hdrs).nvs      , 2 );
	swapbs( (char *)&(*hdrs).nhs      , 2 );
	swapbs( (char *)&(*hdrs).duse     , 2 );
	swapbs( (char *)&(*hdrs).offset   , 4 );
	swapbs( (char *)&(*hdrs).gelev    , 4 );
	swapbs( (char *)&(*hdrs).selev    , 4 );
	swapbs( (char *)&(*hdrs).sdepth   , 4 );
	swapbs( (char *)&(*hdrs).gdel     , 4 );
	swapbs( (char *)&(*hdrs).sdel     , 4 );
	swapbs( (char *)&(*hdrs).swdep    , 4 );
	swapbs( (char *)&(*hdrs).gwdep    , 4 );
	swapbs( (char *)&(*hdrs).scalel   , 2 );
	swapbs( (char *)&(*hdrs).scalco   , 2 );
	swapbs( (char *)&(*hdrs).sx       , 4 );
	swapbs( (char *)&(*hdrs).sy       , 4 );
	swapbs( (char *)&(*hdrs).gx       , 4 );
	swapbs( (char *)&(*hdrs).gy       , 4 );
	swapbs( (char *)&(*hdrs).counit   , 2 );
	swapbs( (char *)&(*hdrs).wevel    , 2 );
	swapbs( (char *)&(*hdrs).swevel   , 2 );
	swapbs( (char *)&(*hdrs).sut      , 2 );
	swapbs( (char *)&(*hdrs).gut      , 2 );
	swapbs( (char *)&(*hdrs).sstat    , 2 );
	swapbs( (char *)&(*hdrs).gstat    , 2 );
	swapbs( (char *)&(*hdrs).tstat    , 2 );
	swapbs( (char *)&(*hdrs).laga     , 2 );
	swapbs( (char *)&(*hdrs).lagb     , 2 );
	swapbs( (char *)&(*hdrs).delrt    , 2 );
	swapbs( (char *)&(*hdrs).muts     , 2 );
	swapbs( (char *)&(*hdrs).mute     , 2 );
	swapbs( (char *)&(*hdrs).ns       , 2 );
	swapbs( (char *)&(*hdrs).dt       , 2 );
	swapbs( (char *)&(*hdrs).gain     , 2 );
	swapbs( (char *)&(*hdrs).igc      , 2 );
	swapbs( (char *)&(*hdrs).igi      , 2 );
	swapbs( (char *)&(*hdrs).corr     , 2 );
	swapbs( (char *)&(*hdrs).sfs      , 2 );
	swapbs( (char *)&(*hdrs).sfe      , 2 );
	swapbs( (char *)&(*hdrs).slen     , 2 );
	swapbs( (char *)&(*hdrs).styp     , 2 );
	swapbs( (char *)&(*hdrs).stas     , 2 );
	swapbs( (char *)&(*hdrs).stae     , 2 );
	swapbs( (char *)&(*hdrs).tatyp    , 2 );
	swapbs( (char *)&(*hdrs).afilf    , 2 );
	swapbs( (char *)&(*hdrs).afils    , 2 );
	swapbs( (char *)&(*hdrs).nofilf   , 2 );
	swapbs( (char *)&(*hdrs).nofils   , 2 );
	swapbs( (char *)&(*hdrs).lcf      , 2 );
	swapbs( (char *)&(*hdrs).hcf      , 2 );
	swapbs( (char *)&(*hdrs).lcs      , 2 );
	swapbs( (char *)&(*hdrs).hcs      , 2 );
	swapbs( (char *)&(*hdrs).year     , 2 );
	swapbs( (char *)&(*hdrs).day      , 2 );
	swapbs( (char *)&(*hdrs).hour     , 2 );
	swapbs( (char *)&(*hdrs).minute   , 2 );
	swapbs( (char *)&(*hdrs).sec      , 2 );
	swapbs( (char *)&(*hdrs).timbas   , 2 );
	swapbs( (char *)&(*hdrs).trwf     , 2 );
	swapbs( (char *)&(*hdrs).grnors   , 2 );
	swapbs( (char *)&(*hdrs).grnofr   , 2 );
	swapbs( (char *)&(*hdrs).grnlof   , 2 );
	swapbs( (char *)&(*hdrs).gaps     , 2 );
	swapbs( (char *)&(*hdrs).otrav    , 2 );
	swapbs( (char *)&(*hdrs).cdp_x    , 4 );
	swapbs( (char *)&(*hdrs).cdp_y    , 4 );
	swapbs( (char *)&(*hdrs).Inline   , 4 );
	swapbs( (char *)&(*hdrs).corssline, 4 );
	swapbs( (char *)&(*hdrs).incident , 4 );
	swapbs( (char *)&(*hdrs).shot     , 4 );
	swapbs( (char *)&(*hdrs).ffile    , 4 );
	swapbs( (char *)&(*hdrs).dimension, 4 );
	
	for( ix=0; ix<14; ix++ )
		swapbs( (char *)((*hdrs).unass+ix)  , 2 );
}
