// g mancini apr 18
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef OMP
	#include <omp.h>
#endif

int mandel(double x0, double y0, double tr, int maxiter)
{
    double re  = 0.0;
    double im  = 0.0;
    double re2 = 0.0;
    double im2 = 0.0;
    int k;
    
    for (k = 1; k < maxiter && (re2 + im2 < tr); k++) 
    {
        im = 2. * re * im + y0;
        re = re2 - im2 + x0;
        re2 = re * re;
        im2 = im * im;
    }    
    return k;
}

void write_output(char* filename, int** image, int width, int height, int maxiter)
{
    
    // open output PPM file, https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
    unsigned char colour[3];
    FILE * fp = fopen(filename,"w");
    fprintf(fp,"P3\n%d %d %d\n",width, height, 255);    
    for (int i=0; i< height; i++)
        for (int j=0; j < width; j++)
        {           
            if(image[i][j] >= maxiter)
            {
                colour[0] = 0;
                colour[1] = 0;
                colour[2] = 0;
            }
            else
            {
                colour[0] = 255;
                colour[1] = 255;
                colour[2] = 255;
            }
            fprintf(fp,"%d %d %d ",colour[0],colour[1],colour[2]);
        }
    fclose(fp);     
}

void main(int argc, char *argv[])
{

    //settings
    int maxiter = 1000;
    double horiz  = 3.0;
    int width   = 2048;
    int height  = 2048;
    double xmin = -2.;
    double xmax =  1.;
    double ymin = -1.2;
    double ymax =  1.2;
    char* filename = "out.ppm";
    
    //allocate image
    int **image = malloc(sizeof(int**) * height);
    for(int i=0; i< height; i++)
        image[i] = malloc(sizeof(int*) * width);
        
    //variables
    int k;
    horiz = horiz*horiz;
    double x0, y0, xres, yres;
    xres = (xmax - xmin)/((double) width);
    yres = (ymax - ymin)/((double) height);
    double re, im, re2, im2; 
    
    //compute map for every pixel
    //y0 = ymin; 
#ifdef OMP
   #pragma omp parallel private(x0,y0) 
    {
    int id = omp_get_thread_num();    
    y0 = ymin + ((double) id) * (ymax - ymin)/((double) omp_get_num_threads());
    #pragma omp for
#else
    y0 = ymin;
#endif
    for (int i=0; i< height; i++)
    {
        x0 = xmin;
        for (int j=0; j < width; j++)
        {
            // mandel called in dyn. scope; x0, y0, k from above setting private
            image[i][j] = mandel(x0,y0,horiz,maxiter);
            x0 = x0 + xres;
        }   
        y0 = y0 + yres;
    }// close on i   
#ifdef OMP
    }// omp parallel
#endif

    write_output( filename, image, width, height, maxiter);
    free(image);
}
