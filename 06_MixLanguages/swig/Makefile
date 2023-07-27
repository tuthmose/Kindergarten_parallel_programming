#Makefile for xdrlib with python SWIG interface
#Giordano Mancini Sept 2012
CC     = gcc
CFLAGS = -O2 -Wall -march=native -mtune=native -msse4.2 -fPIC
F77    = gfortran
FFLAGS = $(CFLAGS)
SHELL  = /bin/sh
OBJECTS = swigmc.o
INCLUDE = swigmc.h 
CPPFLAGS = -I/usr/include/python2.7 -I/usr/lib64/python2.7/site-packages/numpy/core/include/ \
-I/usr/lib/python2.7/site-packages/numpy/core/include/
SWIG     = swig 
SWIGOPT  = -python -Wall
SWIGOBJS = swigmc_wrap.o

all: clean swigmc

swigmc: $(OBJECTS) $(SWIGOBJS)
	$(CC) -shared -o _swigmc.so $(OBJECTS) $(SWIGOBJS)

swigmc_wrap.c: swigmc.i
	$(SWIG) $(SWIGOPT) swigmc.i
	
swigmc_wrap.o: swigmc_wrap.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c swigmc.c swigmc_wrap.c

clean:
	rm -f *.so *.o *.pyc swigmc_wrap.c *py *gch
	
.SUFFIXES : .c .h .o

.c.o:
	$(CC) $(INCLUDE) $(CFLAGS) -c $*.c