#include "integral.h"

 //check cmd line arguments
int main(int argc, char **argv)
{
    int num_steps = 1E8;
    double start  = 0.;
    double end    = 1.;
    
    double I  = 0.;
    double dx = (end-start) / ((double ) num_steps);
    
    double t0 = omp_get_wtime();   
    int num_threads;
    
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
    }
    double sum[num_threads] = {0};
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        for(int i = thread_id; i< num_steps; i = i + num_threads)
        {
            double mid_x = start + dx * ((double ) i + 0.5);
            double mid_y = eval_func(mid_x);
            sum[thread_id] += mid_y;
        }            
    }
    
    for(int i = 0; i< num_threads; i++)
        I += sum[i];
    I *= dx;
    
    double t1 = omp_get_wtime();
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms using " \
    << num_threads << " threads" << std::endl;
    std::cout  << "Integral value = " << I << std::endl;
}