#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

void foo(int ID, int *arr)
{
    arr[ID] = ID*10;
}

int main()
{
    int myArray[10];
    omp_set_num_threads(4); //another function to fix the the number of threads to a desired value
    #pragma omp parallel
    {
        int ID = omp_get_thread_num(); // get a numeric ID unique for each thread; ID is private to each thread
        foo(ID,myArray);  //myArray is shared
    }   // implicit barrier; often people denote with //omp parallel
    
    for (int i = 0; i < 4; i++) printf("%d %d\n",i,myArray[i]); //try to use omp_get_num_threads() in the loop
    return 0;
}