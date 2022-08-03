#include "integral.h"

int main(int argc, char **argv)
{
    
    int num_steps = argv[1] != NULL ? atoi(argv[1]) : 1E8;
    double start = 0.;
    double end   = 1.;
    
    double I  = 0.;
    double dx = (end-start) / ((double ) num_steps);
    
    double t0 = omp_get_wtime();
    for(int i=0; i< num_steps; i++)
    {
        double mid_x = start + dx * ((double ) i + 0.5);
        double mid_y = eval_func(mid_x);
        I += mid_y;
    }
    I *= dx;
    double t1 = omp_get_wtime();
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms" << std::endl;
    std::cout  << "Integral value = " << I << std::endl;
}