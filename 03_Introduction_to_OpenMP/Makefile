CC=gcc
CXX=g++
FC=gfortran
CXXFLAGS= -Wall -fopenmp
OFLAGS= -O2
LDFLAGS=-lm -fopenmp
SHELL   = /bin/sh

ifneq ($(mygcc),)
    CXX = /usr/local/gcc-7.3.0/bin/g++
    FC  = /usr/local/gcc-7.3.0/bin/gfortran
    LDFLAGS += -L/usr/local/gcc-7.3.0/lib64
    CPPFLAGS=-I/usr/local/gcc-7.3.0/include    
endif

ifneq ($(opt),)
    CXXFLAGS  += $(OFLAGS)
endif

FFLAGS = $(CXXFLAGS)

serial: integral.o eval_func.o
	$(CXX) -o integral.exe integral.o eval_func.o $(LDFLAGS)

openmp: integral_omp.o eval_func.o
	$(CXX) -o integral.exe integral_omp.o eval_func.o $(LDFLAGS)
    
openmp_pad: integral_omp_pad.o eval_func.o
	$(CXX) -o integral.exe integral_omp_pad.o eval_func.o $(LDFLAGS)    

f95_serial: integral.fo eval_func.fo
	$(FC) -o integral.exe integral.fo eval_func.fo $(LDFLAGS)
	
f95_omp: integral_omp.fo eval_func.fo
	$(FC) -o integral.exe integral_omp.fo eval_func.fo $(LDFLAGS)
	
integral_omp.fo: eval_func.fo

integral.fo: eval_func.fo 

%.o : %.cc
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@
	
%.fo: %.f95
	$(FC) -c $(FFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean   
clean:
	rm -f integral*o eval_func*o integral.exe myodule.mod