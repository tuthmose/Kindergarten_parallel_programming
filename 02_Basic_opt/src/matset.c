#include "matmul_test.h"

void matset(int *X, int dim, int high)
{
    for (int i = 0;i < dim; i++)
        for(int j = 0; j < dim; j++)
                X[i*dim + j] = rand() % high;
        
}