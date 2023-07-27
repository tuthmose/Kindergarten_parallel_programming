#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("A ");
            #pragma omp task
            printf("race ");
            #pragma omp task
            printf("car ");
            #pragma omp taskwait
            printf(" or a horse one?");
        } //single thread
    } //parallel region
    printf("\n");
    return 0;
}