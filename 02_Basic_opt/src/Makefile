CC=/usr/local/gcc-7.3.0/bin/gcc
CFLAGS= -std=c99 -Wall -fopenmp
OFLAGS= -O3
VFLAGS= -ftree-vectorize -march=native -msse3 -fopt-info-vec-optimized
VFLAG2= -fopenmp-simd -march=native -msse3 -fopt-info-vec-optimized
LDFLAGS=-lm -fopenmp -L/usr/local/gcc-7.3.0/lib64
CPPFLAGS=-I/usr/local/gcc-7.3.0/include
SHELL   = /bin/sh
OBJECTS  = matmul_test.o matset.o matprint.o
   
ifneq ($(vec),)
	CFLAGS  += $(OFLAGS) $(VFLAGS)
endif
   
ifneq ($(opt),)
	CFLAGS  += $(OFLAGS)
endif

all: matmul.exe 

matmul.exe: $(OBJECTS) matmul_blas.o
	$(CC) -o matmul.exe $(OBJECTS) matmul_blas.o $(LDFLAGS)

dot: $(OBJECTS) matmul_dot.o
	$(CC) -o matmul.exe $(OBJECTS) matmul_dot.o $(LDFLAGS)

%.o : %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean	
clean:
	rm -f matmul.exe *.o *.s 