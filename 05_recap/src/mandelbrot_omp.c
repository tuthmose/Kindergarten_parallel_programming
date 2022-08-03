// g mancini apr 18
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>
//g. mancini july 18
inline int mandel(double x0, double y0, double tr, int maxiter)
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

void write_output(char* filename, int* image, int width, int height, int maxiter)
{
    // open output PPM file, https://en.wikipedia.org/wiki/Netpbm_format#PPM_example
    FILE * fp = fopen(filename,"w");
    fprintf(fp,"P3\n%d %d %d\n",width, height, 255);    

    for (int i = 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {           
            if(image[i + j*height] >= maxiter)
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
    const int maxiter   =  500;
    const int width     = 2048;
    const int height    = 2048;
    const double xmin   =   -2.;
    const double xmax   =    1.;
    const double ymin   =   -1.2;
    const double ymax   =    1.2;
    char* filename = "out.ppm";
    double horiz  = 3.0;
    
    //variables
    horiz = horiz*horiz;
    double xres, yres;
    xres = (xmax - xmin)/((double) width);
    yres = (ymax - ymin)/((double) height);
    
    //allocate image
    int *image = malloc(sizeof(int) * height * width); 
    
    // run
#ifdef _OPENMP
    double t0 = omp_get_wtime();
    int block = 8;
    #pragma omp parallel for schedule(dynamic) //collapse(2) 
    for(int jj = 0; jj < width; jj+=block)
        for (int i = 0; i < height; i++)
        {    
            for (int j = jj; j < jj + block; j++)
            {
                double x0 = xmin + j*xres;
                double y0 = ymin + i*yres;
                image[i + j*height] = mandel(x0,y0,horiz,maxiter);                
            }   
        }// close on i   
    
    double t1 = omp_get_wtime();
    printf("spent %f ms in parallel loop\n",(t1-t0)*1000.0);
#else
    double y0 = ymin;
    for (int i = 0; i< height; i++)
    {
        double x0 = xmin;
        for (int j = 0; j < width; j++)
        {
            image[i + j*height] = mandel(x0,y0,horiz,maxiter);
            x0 = x0 + xres;
        }   
        y0 = y0 + yres;
    }// close on i    
#endif
    write_output( filename, image, width, height, maxiter);
    free(image);   
    return 0;
}