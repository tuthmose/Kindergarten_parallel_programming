void matmul(int **a, int **b, int **c, int dim)
{
    for (int i = 0;i < dim; i++)
        for (int j = 0; j < dim; j++)                
            for (int k = 0;k < dim; k++)                 
                a[i][j] += b[i][k] * c[k][j];  
}