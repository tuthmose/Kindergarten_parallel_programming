#include "matmul_test.h"

void matprint(int **a, int dim)
{
    for(int i=0; i < dim; i++)
            printf("%d %d %d\n",a[i][0],a[i][1],a[i][2]);
}