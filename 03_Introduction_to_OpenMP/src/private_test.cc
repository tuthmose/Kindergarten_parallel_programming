#include <iostream>
#include <cstdio>
#include <omp.h>

int main ()
{
    int i = 10;
    float j = 10.;

    #pragma omp parallel private(i) firstprivate(j) 
    {
        int ID = omp_get_thread_num();
        printf("thread ID=%d i=%d j=%f\n",ID,i,j);
        i = 1000  + ID;
        j = 1000. + (float ) ID;
    }
    std::cout << "i, j = " << i << "  " << j << std::endl;
}