#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <omp.h>
//g. mancini july 18
int main(int argc, char **argv)
{
    long num_steps = 1e8;
    const double start  = 0.;
    const double end    = 1.;
    const double dx = (end-start) / ((double ) num_steps);
    double PI = 0.;
    int nt;
    
    int rank, size, provided;
    MPI_Init_thread(0,NULL,MPI_THREAD_FUNNELED,&provided);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0)
        printf("Provided mode %d\n",provided);

    double t0 = MPI_Wtime();
    if(num_steps % size != 0)
        num_steps += num_steps/size;
    int chunk = num_steps / size;
    int i0 = rank*chunk;
    int i1 = (rank+1)*chunk;
    
    double I  = 0.;
    #pragma omp parallel for simd reduction(+:I) 
    for(int i = i0; i < i1; i++)
    {
        nt = omp_get_num_threads();
        double mid_x = start + dx * ((double ) i + 0.5);
        double mid_y = 4.0/(1. + mid_x*mid_x) ;
        I += mid_y;
    }
    MPI_Reduce(&I, &PI, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    PI = PI * dx;
    double t1 = MPI_Wtime();
    MPI_Finalize();
    if(rank==0)
    {
        printf("Loop completed in %f using %d procs and %d threads\n",1000.*(t1-t0),size,nt);
        printf("Integral value %f\n",PI);
    }
}