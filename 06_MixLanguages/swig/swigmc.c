#include <stdio.h>
#include <stdlib.h>
#include "swigmc.h"

double calcpi(double *x, double *y, int npoints){

    int    i, inside=0;
    double r2, pi;
    for(i=0;i<npoints;i++){
        r2 = x[i]*x[i] + y[i]*y[i];
        if(r2<=1.0){
            inside++;
        }
    }

    pi = (4.0* ((double) inside))/ ((double) npoints);
    printf("%f %f\n",x[0],y[0]);
    return pi;
}