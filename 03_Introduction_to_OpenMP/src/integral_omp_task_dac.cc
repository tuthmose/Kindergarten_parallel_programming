#include "integral.h"

double do_work(int first, int last, int min_size, double start, double dx)
{
    double sum = 0.;
    if(last - first < min_size)
    {
        for(int i = first; i < last; i++)
        {
            double mid_x = start + dx * ((double ) i + 0.5);
            double mid_y = eval_func(mid_x);
            sum += mid_y;
        }
    }
    else
    {
        int tsize = (last - first)/2;
        double sum1 = 0.;
        double sum2 = 0.;
        #pragma omp task shared(sum1)
        sum1 = do_work(first, first+tsize, min_size, start, dx);
        #pragma omp task shared(sum2)
        sum2 = do_work(first+tsize, last, min_size, start, dx);
        #pragma omp taskwait
        sum = sum1 + sum2;
    }
    return sum;
}

int main(int argc, char **argv)
{
    
    const int num_steps = 1E8;
    const double start  = 0.;
    const double end    = 1.;
    
    double I  = 0.;
    const double dx = (end-start) / ((double ) num_steps);
    double t0 = omp_get_wtime(); 
    int min_size = num_steps / 10;
    #pragma omp parallel
    {
        #pragma omp single
        I += do_work(0, num_steps, min_size, start, dx);
    } 
    double t1 = omp_get_wtime();
    I *= dx;
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms using " << std::endl;
    std::cout  << "Integral value = " << I << std::endl;
}