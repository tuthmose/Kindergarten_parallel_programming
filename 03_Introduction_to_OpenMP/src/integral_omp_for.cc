#include "integral.h"

int main(int argc, char **argv)
{
    
    int num_steps = 1E8;
    double start  = 0.;
    double end    = 1.;
    
    double I  = 0.;
    double dx = (end-start) / ((double ) num_steps);
    double t0 = omp_get_wtime(); 
    int NN;
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); 
        int num_threads = omp_get_num_threads();
        NN = num_threads;
        double mid_y = 0.;
        
        for(int i=thread_id; i< num_steps; i = i + num_threads)
        {
            double mid_x = start + dx * ((double ) i + 0.5);
            mid_y += eval_func(mid_x);
            
        }
            #pragma omp atomic
            I += mid_y;
    }
    
    I = I * dx;
    double t1 = omp_get_wtime();
    
    std::cout  << "Loop completed in "<< 1000.*(t1-t0) << " ms using " \
    << NN << " threads" << std::endl;
    std::cout  << "Integral value = " << I << std::endl;
}