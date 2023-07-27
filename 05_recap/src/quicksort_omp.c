#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <gsl_rng.h>
//https://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C

void quicksort(int *A, int len) 
{
    if (len < 2) return;
    int i, j, temp;
    //median element
    int pivot = A[len / 2];
    for (i = 0, j = len - 1; ; i++, j--)
    {
        //update position of last element to be moved on the right
        while (A[i] < pivot) i++;
        //update position of last element to be moved on the left
        while (A[j] > pivot) j--;
        if (i >= j) break;

        temp = A[i];
        A[i]     = A[j];
        A[j]     = temp;
    }

    //left branch
    #pragma omp task
    quicksort(A, i);
    //right branch
    #pragma omp task
    quicksort(A + i, len - i);
}

void printA(int *A, int L)
{
    for (int i = 0; i < L; i++) 
        printf("%d ", A[i]); 
    printf("\n");    
}

int main (int argc, char *argv[]) 
{
    int length = atoi(argv[1]);
    int *A = malloc(length * sizeof(int));
    gsl_rng *R = gsl_rng_alloc (gsl_rng_taus);
    gsl_rng_set(R, 211085);
    printf("Generating %d random integers in[%ld,%d]\n",length,gsl_rng_min(R),length);
    for( int i = 0; i < length; i++)
        A[i] =  gsl_rng_uniform_int(R, length);
    gsl_rng_free(R);

#ifdef VRB
        printf("Unsorted array:\n"); 
        printA(A, length);
#endif
 
    double t0 = omp_get_wtime();
    int nt;
    #pragma omp parallel
    {
        nt = omp_get_num_threads();
        {
            #pragma omp single
            quicksort(A, length); 
        }
    }
    
    printf("Sorted in %f with %d threads\n",omp_get_wtime()-t0,nt);
#ifdef VRB        
    printf("Sorted array:\n"); 
    printA(A, length);
#endif        
    return 0;
}