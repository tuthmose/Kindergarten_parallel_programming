#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv) {
        
    int num_steps = argv[1] != NULL ? atoi(argv[1]) : 1E8;

    double x, PI, sum[2] = {0.,0.};

#pragma omp simd safelen(2)
    for (int i = 0; i < num_steps; i++){
        x = (i+0.5)/((double) num_steps);
        sum[i%2] += 4.0/(1.0+x*x);
    }

    PI = (sum[0]+sum[1]) / ((double) num_steps);

    printf("PI: %f\n",PI);
    return 0;
}