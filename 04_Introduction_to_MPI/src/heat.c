#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main()
{
    double H0 = 100., H1 = 100.; 

    int Ncell = 5e2; 
    int Nstep = 1e6; 
    
    double delta_t, delta_x, scalef;
    double *Temp, *Tnew, *swap;    
    
    int rank, size, chunk, first, last;
    
    MPI_Init(0,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (size > 1)
    {   
        if(Ncell % size != 0)
            Ncell = size * (Ncell % size + Ncell / size);            
        chunk = Ncell / size + 2;
        first = 2;
        last  = chunk-2; 
        Temp = calloc(chunk, sizeof(double));
        Tnew = calloc(chunk, sizeof(double));

        if(rank == 0)
            Temp[1] = H0;
        if(rank == size-1)
            Temp[chunk-2] = H1;
    } 
    else
    {
        first = 1;
        last  = Ncell - 1;
        chunk = Ncell;
        
        Temp = calloc(Ncell, sizeof(double));
        Tnew = calloc(Ncell, sizeof(double));        
        Temp[0] = H0;
        Temp[Ncell-1] = H1;        
    }
    
    for(int i = first-1; i <= last+1; i++)
        Tnew[i] = Temp[i];
    
    delta_x = 1. / ((double ) Ncell);
    delta_t = 1. / ((double ) Nstep);
    scalef = delta_t / (delta_x * delta_x);    
    
    if(rank == 0) 
        printf("scalef, Ncell, chunk: %f %d %d \n",scalef,Ncell,chunk);
   
    for(int time = 0; time < Nstep; time++) 
    {   
       if (size > 1)
       {
           // has a left neighbour
            if(rank != 0) 
                MPI_Send(&Temp[1], 1, MPI_DOUBLE, rank-1, rank, MPI_COMM_WORLD);
       
            // has a right neighbour
            if(rank != size - 1) 
            {
                MPI_Recv(&Temp[last+1], 1, MPI_DOUBLE, rank+1, rank+1, MPI_COMM_WORLD, &status);
                MPI_Send(&Temp[last], 1, MPI_DOUBLE, rank+1, rank, MPI_COMM_WORLD);
            }
       
            if(rank != 0) 
                MPI_Recv(&Temp[0], 1, MPI_DOUBLE, rank-1, rank-1, MPI_COMM_WORLD, &status);
       } //endif size > 1

        //apply stencil
        #pragma omp simd
        for(int cell = first; cell < last; cell++) 
            Tnew[cell] = Temp[cell] + scalef * (Temp[cell+1] - 2.*Temp[cell] + Temp[cell-1]);
        
        if(size > 1)
        {
            // 0 is a ghost cell
            if(rank != 0)
                Tnew[1] = Temp[1] + scalef * (Temp[2] - 2.*Temp[1] + Temp[0]);
                
            // chunk+2-1 is a ghost cell
            if(rank != size - 1)
                Tnew[last] = Temp[last] + scalef * (Temp[last+1] - 2.*Temp[last] + Temp[last-1]);
        }
        
        swap = Tnew;
        Tnew = Temp;
        Temp = swap;
        
    } //end for time
    
    if (size > 1)
    {
        swap = calloc(Ncell, sizeof(double)); 
        MPI_Allgather(&Tnew[1],last,MPI_DOUBLE,swap,last,MPI_DOUBLE,MPI_COMM_WORLD);
    }

    MPI_Finalize();

    if (rank == 0) 
    {
        char outname[30] = "temp_field_np_";
	char SZ[10];
	sprintf(SZ,"%d",size);
	strcat(outname, SZ);

	FILE *fp = fopen(outname, "w");
        for(int i = 1; i < Ncell; i++)
            fprintf(fp,"%d %f\n", i, swap[i]); 
	fclose(fp);
    }
    return 0;
}