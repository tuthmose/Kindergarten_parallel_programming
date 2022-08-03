#include "integral.h"

int main(int argc, char **argv)
{
    double a  = atof(argv[1]);
    double b  = atof(argv[2]);
    int n = atoi(argv[3]);
    if(a >= b)
    {
        printf("error: b must be > a\n");
        return -1;
    }
    
    const double dx = (b - a)/n;
    double I = 0.;
    double t0 = omp_get_wtime();    

#ifndef novec
     #pragma omp simd reduction(+: I)
#endif
    for (int i = 0; i < n; i++)
    {
        const double xip12 = a + dx * ((double ) i + 0.5);
        const double yip12 = myfunc(xip12);
        const double dI = yip12 * dx;
        I += dI;
    }
    printf("Loop completed in %g s.\n Integral value=%f\n",omp_get_wtime()-t0,I);
    
}