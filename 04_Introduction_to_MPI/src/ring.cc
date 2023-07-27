#include <iostream>
#include <cstdlib>
#include <string>
#include <mpi.h>
#include <unistd.h>

using namespace std;

int main(int argc, char **argv)
{
    int rank, size, check, to, from;

    string hdr = ": sent to ";
    string ftr = " and received from ";
    char rmsg[35] = " xxx" ;
       
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

    string msg = to_string(rank) + hdr + to_string(to) + ftr + to_string(from);
    
    if (size > 1)
    {
        MPI_Send(&msg[0],35,MPI_BYTE,to,check,MPI_COMM_WORLD);
        MPI_Recv(rmsg,35,MPI_BYTE,from,from,MPI_COMM_WORLD,MPI_STATUS_IGNORE);                
    }
    
    cout << rmsg << endl;
    
    MPI_Finalize();
}