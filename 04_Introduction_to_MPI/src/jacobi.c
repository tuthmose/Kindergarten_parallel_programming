#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <string.h>

double check_jacobi(int dim, double **A, double *b, double *xnew)
{
    double sum = 0.;
    
    for(int i = 0; i < dim; i++)    
    {
        double sum_i = b[i];
        
        for(int j = 0; j < dim; j++)    
            sum_i -= A[i][j] * xnew[j];
        
        sum += pow(sum_i,2);
    }
    
    return sqrt(sum/(double ) dim);
}

void gen_jac_input(int DIM, int high, double **A, double *b, double *xo)
{

    for (int i=0; i < DIM;i++)
    {
        b[i]  = (double ) (rand() % high);
        xo[i] = (double ) (rand() % high);
        double sum = 0.;

        for (int j=0; j< DIM; j++)
        {
            A[i][j] = (double ) (rand() % high);
            sum += A[i][j];
        }
        A[i][i] = 1.5 * (sum - A[i][i]);
    }
}

double do_iter(int rank, int first, int last, int dim, \
               double **A, double *b, double *xold, double *xnew)
{
        double conv = 0.;
        for(int i = first; i < last; i++)
        {
            double tmp = 0.;
            int row = i + rank*last;
            
            #pragma omp simd reduction(+:tmp)
            for(int j = 0; j < dim; j++)
                tmp += xold[j] * A[row][j];

            xnew[i] = (b[row] - tmp + xold[row] * A[row][row])/A[row][row];
            conv += pow(xnew[i]-xold[row],2);
        }    
        return conv;
}

double jacobi(int dim, double **A, double *b, double *xold,\
    double *xnew, double tol, int kmax, int *niter)
{

    int rank, size;
#ifdef MPI_VERSION    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
#else
    rank = 0;
    size = 1;  
#endif    
    
    double gconv = 1. + tol;
    int chunk = dim / size;
    int k = 0;
    
    while(k < kmax && gconv > tol)
    {
        
        double conv = do_iter(rank, 0, chunk, dim, A, b, xold, xnew);
#ifdef MPI_VERSION                           
        if(rank == 0 && dim % size > 0)
        {
            conv += do_iter(0, size*chunk, dim, dim, A, b, xold, xnew);
            for(int i = size*chunk; i < dim; i++)
                xold[i] = xnew[i];
        }
        MPI_Allgather(xnew, chunk, MPI_DOUBLE, xold, chunk, MPI_DOUBLE,
            MPI_COMM_WORLD);

        if(dim % size > 0)
            MPI_Bcast(&xold[size*chunk], dim % size, MPI_DOUBLE, 0, MPI_COMM_WORLD);      
        MPI_Allreduce(&conv, &gconv, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
#else
        gconv = conv;
#endif        
        k++;
    }
    
    memcpy(xnew,xold,sizeof(double) * dim);
    *niter = k;
    return gconv;
}

int main(int argc, char **argv)
{
    double tol = 1e-8;
    const int kmax = 100;
    const int DIM  = atoi(argv[1]);
    const int high = atoi(argv[2]);
    int niter;
    
    double t0 = 0., t1 = 0.;
    srand(23);
    
    //allocate
    double  **A = malloc(DIM * sizeof(double*));
    A[0] =  malloc(DIM * DIM * sizeof(double));
    for(int i = 1; i < DIM; i++)
        A[i] = A[0] + i*DIM;
    double  *b = malloc(DIM * sizeof(double));
    double *xo = malloc(DIM * sizeof(double));
    double *xn = calloc(DIM, sizeof(double));

    //generate A and b and make A diagonally dominant
    gen_jac_input(DIM, high, A, b, xo);
    
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int rank = 0;
    
    //call jacobi 
    t0 = MPI_Wtime();

    double conv = jacobi(DIM, A, b, xo, xn, tol, kmax, &niter);
      
    MPI_Finalize();
    t1 = MPI_Wtime();
    
    if(rank == 0)
    {
        if(niter < kmax)
            printf("converged at %g after %d iterations in %g s\n",conv,niter,t1-t0);
        else 
            printf("NOT converged (conv=%g) after %d iterations\n",conv,niter);
        
        //check results
        double error = check_jacobi(DIM, A, b, xn);
        printf("error=%f\n",error);
    }
   
}