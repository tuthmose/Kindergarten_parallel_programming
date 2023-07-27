#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <x86intrin.h> 
//g. mancini july 18
int main()
{
    const long steps = 1E8;
    const double start = 0.;
    const double end   = 1.;
    
    double I  = 0.;
    const double dx = (end-start) / ((double ) steps);
    double t0 = omp_get_wtime();   
    for(int i=0; i < steps; i++)
    {
        double mid_x = start + dx * ((double ) i + 0.5);
        double mid_y = 1.0/(1. + mid_x*mid_x);
        I += mid_y;
    }
    I = 4. * I * dx;
    double time = 1000.* (omp_get_wtime() - t0);
    printf("PI=%f, evaluated in %f ms\n",I, time);
    I = 0.;
    
    t0 = omp_get_wtime();
    printf("Evalute PI in vectorized loop\n");
    __m128d num = _mm_set_pd(4.,4.);
    __m128d IV  = _mm_set_pd(0.,0.);
    for(int i = 0; i < steps; i = i+2)
    {
        __m128d x = _mm_set_pd(i*dx, (i+1)*dx);
        IV =_mm_add_pd(IV,_mm_div_pd(num,1+_mm_mul_pd(x,x)));
    }
    for(int i = 0; i < 2; i++)
        I += IV[i];
    I = I * dx;
    time = 1000.* (omp_get_wtime() - t0);
    printf("PI=%f, evaluated in %f ms\n",I, time);
    
    return 0; 
}