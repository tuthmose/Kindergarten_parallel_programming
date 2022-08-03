#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <x86intrin.h> 
//g. mancini july 18
int main()
{
    const int steps = 1e7;
    double *arr = calloc(sizeof(double), steps);
    
    printf("non vectorized\n");
    double t0 = omp_get_wtime();  
    for(int i = 0; i < steps; i++)
        arr[i] = (double ) i;
    double time = 1000.*(omp_get_wtime() - t0);
    printf("time=%f\n", time);
    
    printf("intrisics\n");
    int dim = 2; //SSE
    t0  = omp_get_wtime();  
    for(int i = 0; i < steps/dim; i += dim)
    {
        __m128d tmp = {(double ) i+1,(double ) i};
        _mm_storeu_pd(&arr[i], tmp);
    }
    if( steps % dim != 0) 
        for(int i = (steps/dim)*dim; i < steps; i++)
            arr[i] = (double ) i;
    time = 1000.*(omp_get_wtime() - t0);
    printf("time=%f\n", time);

    printf("OpenMP\n");
    t0  = omp_get_wtime();  
    #pragma omp simd
    for(int i=0; i < steps; i++)
        arr[i] = (double ) i;;
    time = 1000.*(omp_get_wtime() - t0);
    printf("time=%f\n", time);
    
    return 0;
}