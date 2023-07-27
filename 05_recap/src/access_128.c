#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <x86intrin.h> 
// g. mancini july 18
int main()
{
    float x[4] = {10., 20., 30., 40.};
    __m128 One =  {10., 20., 30., 40.};
    __m128 Two =  _mm_load_ps(x);
    __m128 Three =  _mm_set_ps(10., 20., 30., 40.);
    for(int v=0; v < 4; v++)
        printf("%d %f %f %f %f\n",v,x[v],One[v],Two[v],Three[v]);
    printf("--------------\n\n");
    
    float y[8] = {10., 20., 30., 40., 50. ,60., 70., 80.};
    __m128 Four = _mm_load_ps(y);
    for(int i=0; i < 2; i++)
        for(int v=0; v < 4; v++)
            printf("%d %d %f %f \n",v,i*4+v,y[i*4+v],Four[i*4+v]);

    return 0;
}