#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <gsl_rng.h>
//g mancini sept 18
//gcc -Wall quick_sort.c -fopenmp -lm -lgsl -lgslcblas -I/usr/include/gsl/^C

void swap(int *a, int *b)
{
    //dereferentiate a and get the value it points to
    int t = *a; 
    //move address a to same loc of pointed by address b
    *a = *b; 
    //now point b to value t
    *b = t;     
}

int partitionArray(int *A, int low, int high)
{
    //take last element
    int pivot = A[high];
    
    //number of found elements smaller than pivot
    //initially is -1 (have no one)
    int last = low - 1;
    
    for (int i = low; i <= high- 1; i++)
    {
        if (A[i] <= pivot)
        {
            // found a smaller element
            last++;   
            //put current element in next available position on the left
            swap(&A[last], &A[i]);
        }
    }
    //put pivot in correct position; last+1 > pivot
    swap(&A[last + 1], &A[high]);
    return last+1;
}

void Quicksort(int *A, int low, int high) 
{
    if ( low <= high)
    {
        int pivot = partitionArray(A, low, high);
        // Left branch
        #pragma omp task
        Quicksort(A, low, pivot - 1); 
        //Right branch
        #pragma omp task
        Quicksort(A, pivot + 1, high);
    }
}

void printA(int *A, int L)
{
    for (int i = 0; i < L; i++) 
        printf("%d ", A[i]); 
    printf("\n");    
}

int main(int argc, char *argv[]) 
{ 
    int length = atoi(argv[1]);
    int *A;
    if ( length == 0 )
    {
        int Arr[]  = {10, 7, 8, 9, 1, 5, 7, 4}; 
        length = sizeof(Arr)/sizeof(Arr[0]); 
        A = Arr;
    }
    else
    {
        int *Arr = malloc(length * sizeof(int));
        gsl_rng *R = gsl_rng_alloc (gsl_rng_taus);
        gsl_rng_set(R, 211085);
        printf("Generating %d random integers in[%ld,%d]\n",length,gsl_rng_min(R),length);
        for( int i = 0; i < length; i++)
            Arr[i] =  gsl_rng_uniform_int(R, length);
        gsl_rng_free(R);
        A = Arr;
    }

    if(length <= 20)
    {
        printf("Unsorted array:\n"); 
        printA(A, length);
    }

    double t0 = omp_get_wtime();
    int nt;
    #pragma omp parallel
    {
        nt = omp_get_num_threads();
        #pragma omp single
        {
            Quicksort(A, 0, length-1); 
        }
    }
    
    if(length <= 20)
    {
        printA(A, length);
    }
    else
    {
        printf("Sorted in %f with %d threads\n",omp_get_wtime()-t0,nt);
#ifdef VRB        
        printf("Sorted array:\n"); 
        printA(A, 20);
        printA(&A[length-20], 20);
#endif        
    }
    return 0; 
} 
