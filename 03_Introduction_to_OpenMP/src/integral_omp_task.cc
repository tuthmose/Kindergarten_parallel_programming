#include "integral.h"

double do_work(int min_size, int *first, int num_steps, double dx, double start)
{
    int tsize = std::min(num_steps - *first, min_size);
    double sum = 0.;
    
    for(int i = *first; i < *first + tsize; i++)
    {
        double mid_x = start + dx * ((double ) i + 0.5);
        sum += eval_func(mid_x);        
    }
    return sum;
}

int main(int argc, char **argv)
{
    const int frac = argv[1] != NULL ? atoi(argv[1]) : 1000;
    const int num_steps = 1E8;
    const int min_size  = num_steps / frac;
    const double start  = 0.;
    const double end    = 1.;
    
    double PI  = 0.;
    const double dx = (end-start) / ((double ) num_steps);
    int done = 0;
    double t0 = omp_get_wtime(); 

    #pragma omp parallel
    {
        #pragma omp single
        while (done < num_steps - min_size)
        {
            double sum = 0.;
            #pragma omp task shared(sum)
                sum = do_work(min_size, &done, num_steps, dx, start);    
            #pragma omp taskwait
            {
                PI += sum;
                done += min_size;
            }
        }
    } 

    PI = (PI + do_work(min_size, &done, num_steps+1, dx, start)) * dx;
    double t1 = omp_get_wtime();
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms using " << std::endl;
    std::cout  << "Integral value = " << PI << std::endl;
}