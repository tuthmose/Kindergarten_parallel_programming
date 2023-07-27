#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <omp.h>

using namespace std;

double eval_func(double a, double dx, int first, int last)
{
    double I = 0.;
    
    #pragma omp simd reduction(+:I)
    for(int i = first; i < last; i++)
    {
        double x = a + dx * ((double ) i + 0.5);
        I += 4./(1. + x*x);
    }
    return I;
}

int main(int argc, char **argv)
{
    
    int num_steps = argv[1] != NULL ? atoi(argv[1]) : 1E8;
    double t0, t1;
    double start = 0.;
    double end   = 1.;
    
    int rank = 0;
    t0 = MPI_Wtime();

    int size;
    MPI::Init(argc, argv);
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    
    double PI = 0.;
    double dx = (end-start) / ((double ) num_steps);
    
    double I = eval_func(start, dx, rank*num_steps/size, (rank+1)*num_steps/size);
    
    MPI::COMM_WORLD.Reduce(&I, &PI, 1, MPI_DOUBLE, MPI_SUM, 0);    
    MPI::Finalize();

    if(rank == 0)
    {
        if(num_steps % size != 0)
        {
            
        }
        PI = (PI)*dx;
        t1 = MPI_Wtime();
        cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms" << endl;
        cout  << "Integral value = " << PI << endl;
    }
}