#include <iostream>
#include <cmath>
#include <omp.h>

int main ()
{
    float j = 10.;
    #pragma omp parallel for lastprivate(j) 
    for(int i=0; i < 1000; i++)
    {
        j = sin((float ) i);
    }
    std::cout << " j = " << j << std::endl;
}