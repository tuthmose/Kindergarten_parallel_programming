#include <iostream>
#include <omp.h>
//g. mancini july 18
int main(int argc, char **argv)
{
    
    const int num_steps = 1e8;
    const double start  = 0.;
    const double end    = 1.;
    
    double I  = 0.;
    const double dx = (end-start) / ((double ) num_steps);
    double t0 = omp_get_wtime();   
    
    #pragma omp parallel for reduction(+:I) schedule(static,1)
    for(int i=0; i < num_steps; i++)
    {
        double mid_x = start + dx * ((double ) i + 0.5);
        double mid_y = 4.0/(1. + mid_x*mid_x) ;
        I += mid_y;
    }
    I = I * dx;
    double t1 = omp_get_wtime();
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms using " << std::endl;
    std::cout  << "Integral value = " << I << std::endl;
}