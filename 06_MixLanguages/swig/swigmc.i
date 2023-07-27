%module swigmc
%{
#define SWIG_FILE_WITH_INIT
#include <stdio.h>
#include <stdlib.h>
#include "swigmc.h"
%}

%include "numpy.i"

%init %{
import_array();
%}

%apply (int DIM1, double* IN_ARRAY1) {(int npx, double* x)};
%apply (int DIM1, double* IN_ARRAY1) {(int npy, double* y)};

%inline %{
        double swigpi(int npx, double* x, int npy, double* y){
                printf("%f %f\n",x[0],y[0]);
                double PI;
                PI = calcpi(x,y,npx);
                return PI;
        }
%}