#include <stdlib.h>
#include <stdio.h>
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
    quicksort(A, i);
    //right branch
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
    int A[] = {10, 7, 8, 9, 1, 5, 7, 4}; 
    int length = sizeof(A)/sizeof(A[0]); 
    printf("Sorted array:\n"); 
    printA(A, length);
    printf("Unsorted array:\n"); 
    quicksort(A, length);
    printA(A, length);
    return 0;
}