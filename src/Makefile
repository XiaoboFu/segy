
CC=/usr/bin/gcc

MAN=../man

I=../include
LIB=../lib

vpath %.h ../include

CFLAGS=-Wall -O2 -g -fPIC -fpic -I$I

objects=swapbs.o swapbhed.o ibm_to_float.o segyread.o segywrite.o\
	write2asc.o getSgyInfo.o MemSetHeader.o DataCopy.o\
	LastGather.o LastTrace.o pickCDPgather.o pickShotgather.o\
	data_convert.o bhed_convert.o segy_convert.o Trace.o

all:	OBJ	\
	lib	\
	libso	\
	segy.1.gz 

OBJ:
	$(CC) -c $(CFLAGS) getSgyInfo.c     -o getSgyInfo.o
	$(CC) -c $(CFLAGS) segyread.c       -o segyread.o
	$(CC) -c $(CFLAGS) segywrite.c      -o segywrite.o
	$(CC) -c $(CFLAGS) write2asc.c      -o write2asc.o
	$(CC) -c $(CFLAGS) swapbs.c         -o swapbs.o
	$(CC) -c $(CFLAGS) swapbhed.c       -o swapbhed.o
	$(CC) -c $(CFLAGS) ibm_to_float.c   -o ibm_to_float.o
	$(CC) -c $(CFLAGS) MemSetHeader.c   -o MemSetHeader.o
	$(CC) -c $(CFLAGS) DataCopy.c       -o DataCopy.o
	$(CC) -c $(CFLAGS) LastGather.c     -o LastGather.o
	$(CC) -c $(CFLAGS) LastTrace.c      -o LastTrace.o
	$(CC) -c $(CFLAGS) pickCDPgather.c  -o pickCDPgather.o
	$(CC) -c $(CFLAGS) pickShotgather.c -o pickShotgather.o
	$(CC) -c $(CFLAGS) data_convert.c   -o data_convert.o
	$(CC) -c $(CFLAGS) bhed_convert.c   -o bhed_convert.o
	$(CC) -c $(CFLAGS) segy_convert.c   -o segy_convert.o
	$(CC) -c $(CFLAGS) Trace.c          -o Trace.o
lib:
	ar rcs libsegy.a $(objects)
#	ar rcs $(LIB)/libsegy.a $(objects)
libso:
	$(CC) -shared -Wall -o libsegy.so $(objects)
#	$(CC) -shared -Wall,-soname,libsegy.so.1 -o $(LIB)/libsegy.so $(objects)

segy.1.gz: $(MAN)/segy.1
	gzip -c $(MAN)/segy.1 > segy.1.gz

.PHONY:clean install
clean:
	-rm -f $(objects) libsegy.a libsegy.so segy.1.gz
install:
	$@ libsegy.so $(LIB)
	$@ libsegy.a  $(LIB)
	$@ segy.1.gz /usr/share/man/man1/

