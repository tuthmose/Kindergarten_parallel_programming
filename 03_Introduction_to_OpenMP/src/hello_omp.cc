#include <iostream>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int nt = omp_get_max_threads();
        std::cout << "Hello World! from thread " << thread_id << "out of " << nt << std::endl;
    }
}