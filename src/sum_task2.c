#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#define cutoff 1000

double sum(double *A, long dim)
{
    if (dim == 0) {
        return 0;
    }
    else if (dim == 1) {
        return A[0];
    }
    else if(dim <= cutoff)
    {
        double x = 0.;
        #pragma omp simd reduction(+:x)
        for(int i = 0; i < dim; i++)
            x += A[i];
        return x;
    }

    long half = dim / 2;
    double x, y;

    #pragma omp parallel
    #pragma omp single nowait
    {
        #pragma omp task shared(x)
        x = sum(A, half);
        #pragma omp task shared(y)
        y = sum(A + sizeof(half), dim - half);
        #pragma omp taskwait
        x += y;
    }
    return x;
}

int main(int argc, char **argv)
{
    long dim  = atol(argv[1]);
    int  high = atoi(argv[2]);
    printf("%ld %d\n",dim,high);
    double *A = malloc(sizeof(double) * dim);
    double check = 0.;
    #pragma omp parallel for simd reduction(+:check)
    for (int i = 0; i < dim; i++)
    {
        A[i] = (double ) (rand() % high);
        check += A[i];
    }
   
    double t0 = omp_get_wtime();
    double S = sum(A, dim);
    double t1 = omp_get_wtime()-t0;
    printf("Sum is %lf vs %lf estimated in %f ms\n",S,check,1000.*t1);
    return 0;
}