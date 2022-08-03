#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
//g. mancini july 18
void main(int argc, char *argv[])
{

    //settings
    const int maxiter = 500;
    double horiz   = 2.0;
    const int width   = 1024;
    const int height  = 1024;
    const double xmin = -2.;
    const double xmax =  1.;
    const double ymin = -1.2;
    const double ymax =  1.2;
    const char* filename = "out.ppm";
        
    //variables
    int k;
    horiz = horiz*horiz;
    double x0, y0, xres, yres;
    xres = (xmax - xmin)/((double) width);
    yres = (ymax - ymin)/((double) height);
    double re, im, re2, im2;
    
    // open output PPM file, https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
    unsigned char colour[3];
    FILE * fp = fopen(filename,"w");
    fprintf(fp,"P3\n%d %d %d\n",width, height, 255);    
    //compute map for every pixel
    //write black &  white out file
}