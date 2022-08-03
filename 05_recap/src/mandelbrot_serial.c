// g mancini apr 18
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <omp.h>
//g. mancini july 18
inline int mandel(double x0, double y0, double thres, int maxiter)
    {
        double re  = 0.0;
        double im  = 0.0;
        double re2 = 0.0;
        double im2 = 0.0;
        int k;
        for (k = 0; k < maxiter && (re2 + im2 < thres); k++) 
        {
            im = 2. * re * im + y0;
            re = re2 - im2 + x0;
            re2 = re * re;
            im2 = im * im;
        }    
        return k;
    }

void write_output(char* filename, int* image, int width, int height, int maxiter)
{
    
    // open output PPM file, https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
    FILE * fp = fopen(filename,"w");
    fprintf(fp,"P3\n%d %d %d\n",width, height, 255);    

    for (int i=0; i< height; i++)
    {
        for (int j=0; j < width; j++)
        {           
            if(image[i + j*height] == maxiter)
                fprintf(fp,"%d %d %d ",0,0,0);
            else
                fprintf(fp,"%d %d %d ",255,255,255);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);     
}
    
int main(int argc, char *argv[])
{
    //settings
    const int maxiter =  500;
    double thres      =    3.0;
    const int width   = 800;
    const int height  = 800;
    const double xmin =   -2.;
    const double xmax =    1.;
    const double ymin =   -1.2;
    const double ymax =    1.2;
    char* filename = "out.ppm";
    //variables
    thres = thres*thres;
    double x0, y0, xres, yres;
    xres = (xmax - xmin)/((double) width);
    yres = (ymax - ymin)/((double) height);
    int *image = malloc(sizeof(int) * height * width); 
    double t0 = omp_get_wtime();
    //calculate
    y0 = ymin;
    for (int i=0; i< height; i++)
    {
        x0 = xmin;
        for (int j=0; j < width; j++)
        {
            image[i + j*height] = mandel(x0,y0,thres,maxiter);
            x0 = x0 + xres;
        }   
        y0 = y0 + yres;
    }// close on i    
    printf("Spent %f seconds\n",omp_get_wtime()-t0);
    write_output( filename, image, width, height, maxiter);
    free(image);
}