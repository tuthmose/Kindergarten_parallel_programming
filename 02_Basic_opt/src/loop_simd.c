void sum(int *a, int *b, int *c, int size)
{   
    #pragma omp simd 
    for(int i=1; i < size; i++)
        a[i] += b[i-1];    

    for(int i=1; i < size; i++)
        a[i] += c[i];       
}