#include "matmul_test.h"
#include <omp.h>

int main(int argc, char **argv)
{
    int n = argv[1] != NULL ? atoi(argv[1]) : 1000; 
    int high = argv[1] != NULL ? atoi(argv[2]) : 100;
    srand(time(0));
    //in practice, do not forget to check for NULL
    
    double t0 = omp_get_wtime();
    int *A = malloc(n * n * sizeof(int));
    int *B = malloc(n * n * sizeof(int));
    int *C = malloc(n * n * sizeof(int));
    
    double t1 = omp_get_wtime();
    printf("spent in allocation %f\n",t1-t0);
    
    matset(A,n,high);
    matset(B,n,high);
    matset(C,n,high);
    double t2 = omp_get_wtime();
    printf("spent in set %f\n",t2-t1);
    
    matmul(A,B,C,n);
    double t3 = omp_get_wtime();
    printf("spent in multiplication %f\n",t3-t2);
}