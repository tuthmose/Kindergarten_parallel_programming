#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fib(unsigned *seq, unsigned position)
{
    seq[position] = seq[position-1]+seq[position-2];
    //return seq[position];
}

int main(int argc, char **argv)
{
    const unsigned L = argv[1] != NULL ? atoi(argv[1]) : 1E8; 
    unsigned  *F = calloc(L,sizeof(unsigned));
    
    F[0] = 0;
    F[1] = 1;
    
    if(L>1)
    {
        double t0 = omp_get_wtime();
        for (unsigned i = 2; i <= L; i++)
        {
            fib(F,i);
        }
        printf("spent in loop %f\n",omp_get_wtime()-t0);        
    }
  return F[L];
}