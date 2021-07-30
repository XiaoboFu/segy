
#ifndef SEGY_H
#define SEGY_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define IBM 1
#define IEEE 5

#ifdef __cplusplus
extern "C"{
#endif

typedef struct  {	/* segy - trace identification header */

    int tracl;	/* Trace sequence number within line
                    --numbers continue to increase if the
                    same line continues across multiple
                    SEG Y files.
                    byte# 1-4
                    */

    int tracr;	/* Trace sequence number within SEG Y file
                    ---each file starts with trace sequence
                    one
                    byte# 5-8
                    */

    int fldr;	/* Original field record number
                    byte# 9-12
                    */

    int tracf;	/* Trace number within original field record
                    byte# 13-16
                    */

    int ep;		/* energy source point number
                    ---Used when more than one record occurs
                    at the same effective surface location.
                    byte# 17-20
                    */

    int cdp;	/* Ensemble number (i.e. CDP, CMP, CRP,...)
                    byte# 21-24
                    */

    int cdpt;	/* trace number within the ensemble
                    ---each ensemble starts with trace number one.
                    byte# 25-28
                    */

    short trid;	/* trace identification code:
                    -1 = Other
                    0 = Unknown
                    1 = Seismic data
                    2 = Dead
                    3 = Dummy
                    4 = Time break
                    5 = Uphole
                    6 = Sweep
                    7 = Timing
                    8 = Water break
                    9 = Near-field gun signature
                    10 = Far-field gun signature
                    11 = Seismic pressure sensor
                    12 = Multicomponent seismic sensor
                    - Vertical component
                    13 = Multicomponent seismic sensor
                    - Cross-line component
                    14 = Multicomponent seismic sensor
                    - in-line component
                    15 = Rotated multicomponent seismic sensor
                    - Vertical component
                    16 = Rotated multicomponent seismic sensor
                    - Transverse component
                    17 = Rotated multicomponent seismic sensor
                    - Radial component
                    18 = Vibrator reaction mass
                    19 = Vibrator baseplate
                    20 = Vibrator estimated ground force
                    21 = Vibrator reference
                    22 = Time-velocity pairs
                    23 ... N = optional use
                    (maximum N = 32,767)

                    Following are CWP id flags:

                    109 = autocorrelation
                    110 = Fourier transformed - no packing
                    xr[0],xi[0], ..., xr[N-1],xi[N-1]
                    111 = Fourier transformed - unpacked Nyquist
                    xr[0],xi[0],...,xr[N/2],xi[N/2]
                    112 = Fourier transformed - packed Nyquist
                    even N:
                    xr[0],xr[N/2],xr[1],xi[1], ...,
                    xr[N/2 -1],xi[N/2 -1]
                    (note the exceptional second entry)
                    odd N:
                    xr[0],xr[(N-1)/2],xr[1],xi[1], ...,
                    xr[(N-1)/2 -1],xi[(N-1)/2 -1],xi[(N-1)/2]
                    (note the exceptional second & last entries)
                    113 = Complex signal in the time domain
                    xr[0],xi[0], ..., xr[N-1],xi[N-1]
                    114 = Fourier transformed - amplitude/phase
                    a[0],p[0], ..., a[N-1],p[N-1]
                    115 = Complex time signal - amplitude/phase
                    a[0],p[0], ..., a[N-1],p[N-1]
                    116 = Real part of complex trace from 0 to Nyquist
                    117 = Imag part of complex trace from 0 to Nyquist
                    118 = Amplitude of complex trace from 0 to Nyquist
                    119 = Phase of complex trace from 0 to Nyquist
                    121 = Wavenumber time domain (k-t)
                    122 = Wavenumber frequency (k-omega)
                    123 = Envelope of the complex time trace
                    124 = Phase of the complex time trace
                    125 = Frequency of the complex time trace
                    130 = Depth-Range (z-x) traces
                    201 = Seismic data packed to bytes (by supack1)
                    202 = Seismic data packed to 2 bytes (by supack2)
                    byte# 29-30
                    */

    short nvs;	/* Number of vertically summed traces yielding
                    this trace. (1 is one trace,
                    2 is two summed traces, etc.)
                    byte# 31-32
                    */

    short nhs;	/* Number of horizontally summed traces yielding
                    this trace. (1 is one trace
                    2 is two summed traces, etc.)
                    byte# 33-34
                    */

    short duse;	/* Data use:
                    1 = Production
                    2 = Test
                    byte# 35-36
                    */

    int offset;	/* Distance from the center of the source point
                    to the center of the receiver group
                    (negative if opposite to direction in which
                    the line was shot).
                    byte# 37-40
                    */

    int gelev;	/* Receiver group elevation from sea level
                    (all elevations above the Vertical datum are
                    positive and below are negative).
                    byte# 41-44
                    */

    int selev;	/* Surface elevation at source.
                    byte# 45-48
                    */

    int sdepth;	/* Source depth below surface (a positive number).
                    byte# 49-52
                    */

    int gdel;	/* Datum elevation at receiver group.
                    byte# 53-56
                    */

    int sdel;	/* Datum elevation at source.
                    byte# 57-60
                    */

    int swdep;	/* Water depth at source.
                    byte# 61-64
                    */

    int gwdep;	/* Water depth at receiver group.
                    byte# 65-68
                    */

    short scalel;	/* Scalar to be applied to the previous 7 entries
                       to give the real value.
                       Scalar = 1, +10, +100, +1000, +10000.
                       If positive, scalar is used as a multiplier,
                       if negative, scalar is used as a divisor.
                       byte# 69-70
                       */

    short scalco;	/* Scalar to be applied to the next 4 entries
                       to give the real value.
                       Scalar = 1, +10, +100, +1000, +10000.
                       If positive, scalar is used as a multiplier,
                       if negative, scalar is used as a divisor.
                       byte# 71-72
                       */

    int  sx;	/* Source coordinate - X
                    byte# 73-76
                    */

    int  sy;	/* Source coordinate - Y
                    byte# 77-80
                    */

    int  gx;	/* Group coordinate - X
                    byte# 81-84
                    */

    int  gy;	/* Group coordinate - Y
                    byte# 85-88
                    */

    short counit;	/* Coordinate units: (for previous 4 entries and
                        for the 7 entries before scalel)
                        1 = Length (meters or feet)
                        2 = Seconds of arc
                        3 = Decimal degrees
                        4 = Degrees, minutes, seconds (DMS)

                        In case 2, the X values are longitude and
                        the Y values are latitude, a positive value designates
                        the number of seconds east of Greenwich
                        or north of the equator

                        In case 4, to encode +-DDDMMSS
                        counit = +-DDD*10^4 + MM*10^2 + SS,
                        with scalco = 1. To encode +-DDDMMSS.ss
                        counit = +-DDD*10^6 + MM*10^4 + SS*10^2
                        with scalco = -100.
                        byte# 89-90
                        */

    short wevel;	/* Weathering velocity.
                        byte# 91-92
                        */

    short swevel;	/* Subweathering velocity.
                        byte# 93-94
                        */

    short sut;	/* Uphole time at source in milliseconds.
                    byte# 95-96
                    */

    short gut;	/* Uphole time at receiver group in milliseconds.
                    byte# 97-98
                    */

    short sstat;	/* Source static correction in milliseconds.
                        byte# 99-100
                        */

    short gstat;	/* Group static correction  in milliseconds.
                        byte# 101-102
                        */

    short tstat;	/* Total static applied  in milliseconds.
                        (Zero if no static has been applied.)
                        byte# 103-104
                        */

    short laga;	/* Lag time A, time in ms between end of 240-
                    byte trace identification header and time
                    break, positive if time break occurs after
                    end of header, time break is defined as
                    the initiation pulse which maybe recorded
                    on an auxiliary trace or as otherwise
                    specified by the recording system
                    byte# 105-106
                    */

    short lagb;	/* lag time B, time in ms between the time break
                    and the initiation time of the energy source,
                    may be positive or negative
                    byte# 107-108
                    */

    short delrt;	/* delay recording time, time in ms between
                        initiation time of energy source and time
                        when recording of data samples begins
                        (for deep water work if recording does not
                        start at zero time)
                        byte# 109-110
                        */

    short muts;	/* mute time--start
                    byte# 111-112
                    */

    short mute;	/* mute time--end
                    byte# 113-114
                    */

    unsigned short ns;	/* number of samples in this trace
                            byte# 115-116
                            */

    unsigned short dt;	/* sample interval; in micro-seconds
                            byte# 117-118
                            */

    short gain;	/* gain type of field instruments code:
                    1 = fixed
                    2 = binary
                    3 = floating point
                    4 ---- N = optional use
                    byte# 119-120
                    */

    short igc;	/* instrument gain constant
                    byte# 121-122
                    */

    short igi;	/* instrument early or initial gain
                    byte# 123-124
                    */

    short corr;	/* correlated:
                    1 = no
                    2 = yes
                    byte# 125-126
                    */

    short sfs;	/* sweep frequency at start
                    byte# 127-128
                    */

    short sfe;	/* sweep frequency at end
                    byte# 129-130
                    */

    short slen;	/* sweep length in ms
                    byte# 131-132
                    */

    short styp;	/* sweep type code:
                    1 = linear
                    2 = cos-squared
                    3 = other
                    byte# 133-134
                    */

    short stas;	/* sweep trace length at start in ms
                    byte# 135-136
                    */

    short stae;	/* sweep trace length at end in ms
                    byte# 137-138
                    */

    short tatyp;	/* taper type: 1=linear, 2=cos^2, 3=other
                        byte# 139-140
                        */

    short afilf;	/* alias filter frequency if used
                        byte# 141-142
                        */

    short afils;	/* alias filter slope
                        byte# 143-144
                        */

    short nofilf;	/* notch filter frequency if used
                        byte# 145-146
                        */

    short nofils;	/* notch filter slope
                        byte# 147-148
                        */

    short lcf;	/* low cut frequency if used
                    byte# 149-150
                    */

    short hcf;	/* high cut frequncy if used
                    byte# 151-152
                    */

    short lcs;	/* low cut slope
                    byte# 153-154
                    */

    short hcs;	/* high cut slope
                    byte# 155-156
                    */

    short year;	/* year data recorded
                    byte# 157-158
                    */

    short day;	/* day of year
                    byte# 159-160
                    */

    short hour;	/* hour of day (24 hour clock)
                    byte# 161-162
                    */

    short minute;	/* minute of hour
                        byte# 163-164
                        */

    short sec;	/* second of minute
                    byte# 165-166
                    */

    short timbas;	/* time basis code:
                        1 = local
                        2 = GMT
                        3 = other
                        byte# 167-168
                        */

    short trwf;	/* trace weighting factor, defined as 1/2^N
                    volts for the least sigificant bit
                    byte# 169-170
                    */

    short grnors;	/* geophone group number of roll switch
                        position one
                        byte# 171-172
                        */

    short grnofr;	/* geophone group number of trace one within
                        original field record
                        byte# 173-174
                        */

    short grnlof;	/* geophone group number of last trace within
                        original field record
                        byte# 175-176
                        */

    short gaps;	/* gap size (total number of groups dropped)
                    byte# 177-178
                    */

    short otrav;	/* overtravel taper code:
                        1 = down (or behind)
                        2 = up (or ahead)
                        byte# 179-180
                        */

    /* next defined by Xiaobo.Foo from College of Geophysics, Chengdu University of Technology */
    /* next defined by Xiaobo.Foo from College of Geophysics, Chengdu University of Technology */
    int cdp_x;/* CDP X coordinate
                    byte# 181-184
                                */
    int cdp_y;/* CDP Y coordinate
                 byte# 185-188
                                */
    int Inline;/* the NO. of Inline
                  byte# 189-192
                                 */
    int corssline; /* corssline number
                      byte# 193-196
                    */
    int incident;/* incident angle the units are degree not radian.
                    byte# 197-200
                  */
    int ntrac; /* number of traces
                  byte# 201-204
                */
    int ffile; /* file NO.
                  byte# 205-208
                */
    int dimension;/* 2D, 3D
                     0=2D
                     1=3D
                     byte# 209-212
                   */
    short int unass[14]; /*unassigned--for optional info*/

}segy;


typedef struct {	/* bhed - binary header */

    char commend[3200];

    int jobid;	/* job identification number */

    int lino;	/* line number (only one line per reel) */

    int reno;	/* reel number */

    short ntrpr;	/* number of data traces per record */

    short nart;	/* number of auxiliary traces per record */

    unsigned short hdt; /* sample interval in micro secs for this reel */

    unsigned short dto; /* same for original field recording */

    unsigned short hns; /* number of samples per trace for this reel */

    unsigned short nso; /* same for original field recording */

    short format;	/* data sample format code:
                        1 = floating point, 4 byte (32 bits)
                        2 = fixed point, 4 byte (32 bits)
                        3 = fixed point, 2 byte (16 bits)
                        4 = fixed point w/gain code, 4 byte (32 bits)
                        5 = IEEE floating point, 4 byte (32 bits)
                        8 = two's complement integer, 1 byte (8 bits)
                        */

    short fold;	/* CDP fold expected per CDP ensemble */

    short tsort;	/* trace sorting code:
                        1 = as recorded (no sorting)
                        2 = CDP ensemble
                        3 = single fold continuous profile
                        4 = horizontally stacked */

    short vscode;	/* vertical sum code:
                        1 = no sum
                        2 = two sum ...
                        N = N sum (N = 32,767) */

    short hsfs;	/* sweep frequency at start */

    short hsfe;	/* sweep frequency at end */

    short hslen;	/* sweep length (ms) */

    short hstyp;	/* sweep type code:
                        1 = linear
                        2 = parabolic
                        3 = exponential
                        4 = other */

    short schn;	/* trace number of sweep channel */

    short hstas;	/* sweep trace taper length at start if
                        tapered (the taper starts at zero time
                        and is effective for this length) */

    short hstae;	/* sweep trace taper length at end (the ending
                        taper starts at sweep length minus the taper
                        length at end) */

    short htatyp;	/* sweep trace taper type code:
                        1 = linear
                        2 = cos-squared
                        3 = other */

    short hcorr;	/* correlated data traces code:
                        1 = no
                        2 = yes */

    short bgrcv;	/* binary gain recovered code:
                        1 = yes
                        2 = no */

    short rcvm;	/* amplitude recovery method code:
                    1 = none
                    2 = spherical divergence
                    3 = AGC
                    4 = other */

    short mfeet;	/* measurement system code:
                        1 = meters
                        2 = feet */

    short polyt;	/* impulse signal polarity code:
                        1 = increase in pressure or upward
                        geophone case movement gives
                        negative number on tape
                        2 = increase in pressure or upward
                        geophone case movement gives
                        positive number on tape */

    short vpol;	/* vibratory polarity code:
                    code	seismic signal lags pilot by
                    1	337.5 to  22.5 degrees
                    2	 22.5 to  67.5 degrees
                    3	 67.5 to 112.5 degrees
                    4	112.5 to 157.5 degrees
                    5	157.5 to 202.5 degrees
                    6	202.5 to 247.5 degrees
                    7	247.5 to 292.5 degrees
                    8	293.5 to 337.5 degrees */

    short hunass[170];	/* unassigned */

} bhed;

 void float_to_ibm(int from[], int to[], int n, int endian);
 void ibm_to_float(int from[], int to[], int n, int endian, int verbose);
 void short_to_float(short from[], float to[], int n, int endian);
 void integer1_to_float(signed char from[], float to[], int n);
 void int_to_float(int from[], float to[], int n, int endian);

 void swapbhed(bhed *rh);
 void swaphdrs(segy *hdrs);
 void swapbs(char *buf, short size);

 void bhed_convert(bhed *re_h, int *big);
 void segy_convert(segy *tr_h, int big);
 void data_convert(float *seis_data, int tr_len, int big, int format);

//int getSgyInfo(char *ifile, bhed *re, int *ntrace, int *ns, int *dt);
 int getSgyInfo(FILE *_File, bhed *re);
 int getSgyInfochar(char *ifile, bhed *re, int *ntrace, int *ns, int *dt);

//int segyread(char *ifile, segy *tr, float *trace, int cTrace);
 int _segyread(FILE *_File, segy *tr, float *trace, bhed re);
 int _segywrite(FILE *_File, bhed re, segy tr, float *trace, int format, int cTrace);
 int segyread(char *file, segy*tr, float*trace, bhed re, int cTrace);
 int segywrite(char *file, bhed re, segy tr, float *trace, int format, int cTrace);
//int segywrite(char *ofile, bhed re, segy tr, float *trace, int format, int cTrace);
 void write2asc(char *ofile, bhed re_h, segy  tr_h, float *seis_data, int cTrace);
 void MemSetReelHead(bhed* re_h);
 void MemSetTraceHead(segy* tr_h);

 void headCopy(segy *targ, segy from, int id);
 void traceCopy(float *targ, float *from, int size, int id);
 int LastGather(int, int);
 int LastTrace(int, int);

 void pickCDPgather(char *file, segy *trBuf, float *traceBuf, long int *size, int *ntr, int *flag);
 void pickShotgather(char *file, segy *trBuf, float *traceBuf, long int *size, int *ntr, int *flag);

 void swap_short_2(short *tni2);
 void swap_u_short_2(unsigned short *tni2);
 void swap_int_4(int *tni4);
 void swap_u_int_4(unsigned int *tni4);
 void swap_long_4(long *tni4);
 void swap_u_long_4(unsigned long *tni4);
 void swap_float_4(float *tnf4);
 void swap_double_8(double *tndd8);


typedef struct {
    int CDPNO;
    long int cdpIndex;

}Line;

typedef struct {
    int InLine;
    int CDP;
    int nTrace;
    long int offset;

}preIndex;

typedef struct SEGYINFO{
    int minLine;
    int maxLine;
    int minXLine;
    int maxXLine;
    int LineInc;
    int XLineInc;
    int ns;
    int ntrace;
    int dt;
    int delrt;

    SEGYINFO(){
        minLine=0;
        maxLine=0;
        minXLine=0;
        maxXLine=0;
        LineInc=0;
        XLineInc=0;
        ns=0;
        ntrace=0;
        dt=0;
        delrt=0;
    }
}segyInfo;

#ifdef __cplusplus
}
#endif

#endif
