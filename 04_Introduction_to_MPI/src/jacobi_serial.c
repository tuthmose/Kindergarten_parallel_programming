#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

double check_jacobi(int dim, double *A, double *b, double *xnew)
{
    double sum = 0.;
    for(int i = 0; i < dim; i++)    
    {
        double sum_i = b[i];
        for(int j = 0; j < dim; j++)    
            sum_i -= A[i + j*dim] * xnew[j];
        sum += pow(sum_i,2);
    }
    
    return sqrt(sum/(double ) dim);
}


double jacobi(int dim, double *A, double *b, double *xold, double *xnew, double tol, int kmax, int *niter)
{
    int k = 0;
    double conv = (double ) kmax;
    double tmp; 

    while(k < kmax && conv > tol)
    {
        conv = 0. ;
        for(int i = 0; i < dim; i++)
        {
            tmp = 0.;
            for(int j = 0; j < dim; j++)            
            {
                if (i==j) continue;                
                tmp += xold[j] * A[i + j*dim];
            }
            xnew[i] = (b[i] - tmp)/A[i + i*dim];
            conv += pow((xnew[i]-xold[i]),2);
        }
        for(int i = 0; i < dim; i++)
            xold[i] = xnew[i];
        k++;
    }
    
    *niter = k;
    return conv;
}

int main(int argc, char **argv)
{
    //argv1 DIM argv2 high
    double tol = 1e-8;
    int kmax = 100;
    int DIM  = atoi(argv[1]);
    int high = atoi(argv[2]);
    int niter;
    srand(time(0));
    
    //allocate
    double *A  = malloc(DIM * DIM * sizeof(double));   
    double *b  = malloc(DIM * sizeof(double));
    double *xo = malloc(DIM * sizeof(double));
    double *xn = calloc(DIM, sizeof(double));

    //generate A and b and make A diagonally dominant
    for (int i=0; i < DIM;i++)
    {
        b[i]  = (double ) (rand() % high);
        xo[i] = (double ) (rand() % high);
        double sum = 0.;
        for (int j=0; j< DIM; j++)
        {
            if (i==j) continue;
            A[i + j*DIM] = (double ) (rand() % high);
            sum += A[i + j*DIM];
        }
        A[i + i*DIM] = 1.5 * sum;
    }
    
    //call jacobi
    double t0 = omp_get_wtime();
    double conv = jacobi(DIM, A, b, xo, xn, tol, kmax, &niter);
    if(niter < kmax)
        printf("converged at %g after %d iterations in %g s\n",conv,niter,omp_get_wtime()-t0);
    else
        printf("NOT converged (tol=%g) after %d iterations\n",conv,niter);
    
    //check results
    double error = check_jacobi(DIM, A, b, xn);
    printf("error=%f\n",error);
   
}