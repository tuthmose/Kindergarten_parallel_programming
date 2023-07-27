#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>

long GDC(long A, long B)
{
    if(B==0)
        return A;
    else
        return GDC(B, A%B);
}

long MTGDC(long A, long B)
{
    if(B==0)
        return A;
    else
        return GDC(B, A%B);
}

int main(int argc, char **argv)
{
    long A = atol(argv[1]);
    long B = atol(argv[2]);
    
    double t0 = omp_get_wtime();
    long C = GDC(A,B);
    printf("GDC %ld estimated in %f ms\n",C,1000.*(omp_get_wtime()-t0));
    return 0;
}