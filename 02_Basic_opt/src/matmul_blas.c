void matmul(int *__restrict a, int *__restrict b, int *__restrict c, int dim)
{
    for (int i = 0;i < dim; i++)
        for (int k = 0;k < dim; k++) 
        {
            int temp = b[i*dim + k];
            #pragma omp simd
            for (int j = 0; j < dim; j++)                               
                a[i*dim + j] += temp * c[k*dim + j];  
        }
}