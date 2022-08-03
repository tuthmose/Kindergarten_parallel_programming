#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
//g. mancini july 18
int main(int argc, char **argv)
{
    int rank, size, check, to, from;

    const char hdr[11] = ": sent to ";
    const char ftr[20] = " and received from ";
    char msg[33], rmsg[33] = " xxx" ;
    
    MPI_Request ReqS, ReqR;
    MPI_Status  Stat;       
    MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    check = rank % size;   
    if (check == 0)
    {
        to   = 1;
        from = size -1;
    } 
    else if (check == size-1)
    {
        to   = 0;
        from = rank -1; 
    }
    else
    {
        to   = check + 1;
        from = check - 1; 
    }

    snprintf(msg,sizeof(msg),"%d%s%d%s%d",rank,hdr,to,ftr,from);
    if (size > 1)
    {
        MPI_Isend(&msg[0], 35, MPI_BYTE, to, check, MPI_COMM_WORLD, &ReqS);
        MPI_Irecv(rmsg,35, MPI_BYTE, from, from, MPI_COMM_WORLD, &ReqR);                
        MPI_Wait(&ReqS, &Stat);
        MPI_Wait(&ReqR, &Stat);
        printf("%s \n",rmsg);
    }
    MPI_Finalize();
}