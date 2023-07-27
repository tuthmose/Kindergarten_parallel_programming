#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
 
int main()
{
   
    int steps = 1e5;
    int dim = 512;
    int hist = 50;
    double t0, t1, sd, mean = 0., var = 0.;
    
    float **X = malloc(steps * sizeof(float*));
    X[0] = malloc(steps * dim * sizeof(float));
    for(int i = 1; i < steps; i++)
        X[i] = X[0] + i*dim; 
    
    float **Y = malloc(steps * sizeof(float*));
    Y[0] = malloc(steps * dim * sizeof(float));
    for(int i = 1; i < steps; i++)
        Y[i] = Y[0] + i*dim; 
#ifndef BLK    
    printf("non block\n");
    for(int h = 0; h < hist; h++)
    {
        t0 = omp_get_wtime();
        for(int i = 0; i<steps; i++) 
            #pragma omp simd
            for(int j = 0; j < dim; j++)
                Y[i][j] = 2*X[i][j];
        t1 = omp_get_wtime() - t0;
        mean += t1;
        var += t1*t1;
    }
#else        
    printf("block\n");
    for(int h = 0; h < hist; h++)
    {
        t0 = omp_get_wtime();
        int block = 16;
        for(int jj = 0; jj < dim; jj += block)
            for(int i = 0; i < steps; i++) 
                //#pragma omp simd
                for(int j = jj; j < jj+block; j++)
                    Y[i][j] = 2*X[i][j];
        t1 = omp_get_wtime() - t0;
        mean += t1;
        var += t1*t1;
    }
#endif
    mean = mean/((double) hist);
    sd = sqrt(var/((double) hist) - mean*mean);
    printf("mean=%f sd=%f\n",mean,sd);   
    
    return 0;
}
