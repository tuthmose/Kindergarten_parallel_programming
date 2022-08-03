#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void matset(int *X, int dim, int high);
void matmul(int *__restrict a, int *__restrict b, int *__restrict c, int dim);