#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void set(int *a,int size)
{
    for(int i = 0; i < size; i++)
        a[i] = i;
}

void sum(int *__restrict a, int *__restrict b, int size)
{
    for(int i=0; i < size; i++)
        a[i] += b[i];    
}

int main()
{

    const int size = 1 << 16;
    int *A = calloc(sizeof(int),size);
    int *B = calloc(sizeof(int),size);
    
    set(A,size);
    set(B,size);
    
    double t0 = omp_get_wtime();
    sum(A,B,size);
    int last = A[size-1]/2;
    printf("%g %d\n",omp_get_wtime()-t0,last);
}