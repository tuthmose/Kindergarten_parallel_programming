CC=gcc -std=c99
CXX=g++ 
FC=gfortran -std=gnu
CXXFLAGS= -Wall -fopt-info-vec-optimized -march=native -msse4.2  #-mavx
LDFLAGS=-lm -lmpi

ifneq ($(ubuntu),)
    MPICC=mpicc.openmpi -std=c99
    MPICXX=mpicxx.openmpi
    MPIFC=mpifort.openmpi
else
    MPICC=mpicc -std=c99
    MPICXX=mpicxx
    MPIFC=mpif90
endif
	
ifneq ($(mygcc),)
    CXX = /usr/local/gcc-7.3.0/bin/g++
    FC  = /usr/local/gcc-7.3.0/bin/gfortran
    LDFLAGS += -L/usr/local/gcc-7.3.0/lib64
    CPPFLAGS=-I/usr/local/gcc-7.3.0/include    
endif

ifneq ($(opt),)
    CXXFLAGS += $(opt)
    LDFLAGS += -fopenmp
endif

FFLAGS = $(CXXFLAGS)
CFLAGS = $(CXXFLAGS)

hello: hello.o
	$(MPICXX) -o hello.exe hello.o $(LDFLAGS)

pingpong: pingpong.o
	$(MPICXX) -o pingpong.exe pingpong.o $(LDFLAGS)

deadlock: deadlock.o
	$(MPICXX) -o deadlock.exe deadlock.o $(LDFLAGS)

ring: ring.o
	$(MPICXX) -o ring.exe ring.o $(LDFLAGS)

integral: integral.o
	$(MPICXX) -o integral.exe integral.o $(LDFLAGS)

jacobi: jacobi.o
	$(MPICC) -o jacobi.exe jacobi.o $(LDFLAGS)

heat_serial: heat_serial.o
	$(CXX) -o heat_serial.exe heat_serial.o $(LDFLAGS)

heat: heat.o
	$(MPICC) -o heat.exe heat.o $(LDFLAGS)
    
f95jacobi: jacobi.fo
	$(MPIFC) -o jacobi.exe jacobi.fo $(LDFLAGS)
	
f95hello: hello.fo
	$(MPIFC) -o hello.exe hello.fo $(LDFLAGS)

f95pingpong: pingpong.fo
	$(MPIFC) -o pingpong.exe pingpong.fo $(LDFLAGS)
	
f95ring: ring.fo
	$(MPIFC) -o ring.exe ring.fo $(LDFLAGS)

%.o : %.c
	$(MPICC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	
%.o : %.cc
	$(MPICXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

%.fo: %.f95
	$(MPIFC) -c $(FFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean   
clean:
	rm -f *.o *.exe