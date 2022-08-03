#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
//#include <gsl_rng.h>
//g mancini sept 18
//gcc -O2 -fopenmp omp_device_dot.c  -lm -lgsl -lgslcblas -I/usr/include/gsl/ -foffload=nvptx-none 
// gcc -O3 -fopenmp -foffload="-lm" omp_device_hello.c 


int main()
{
    int size = 1e3;
    float *A = malloc(size * sizeof(float));
    float *B = malloc(size * sizeof(float));
    float *C = malloc(size * sizeof(float));
    
    // gsl_rng *R = gsl_rng_alloc (gsl_rng_taus);
    // gsl_rng_set(R, 211085);
    for( int i = 0; i < size; i++)
    {
        A[i] =  2. ; // *gsl_rng_uniform(R)-1.;
        B[i] =  2. ; // *gsl_rng_uniform(R)-1.;
    }
    // gsl_rng_free(R);
    
    double t0 = omp_get_wtime();
    #pragma omp parallel for 
    for( int i = 0; i < size; i++)
        C[i] = A[i] * B[i];
    printf("OMP parallel on CPU took %f ms\n",1000.*(omp_get_wtime()-t0));
    
    t0 = omp_get_wtime();
    #pragma omp target map(to:A,B) map(from:C)
    {
        //#pragma omp parallel reduction(+:dot)
        for( int i = 0; i < size; i++)
            C[i] += A[i] * B[i];
    }
    printf("OMP parallel on GPU took %f ms\n",1000.*(omp_get_wtime()-t0));
    return 0;
}
