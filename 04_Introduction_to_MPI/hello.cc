#include <iostream>
#include <cstdlib>
#include <mpi.h>

using namespace std;

int main()
{
    int rank, size;
   
    //start MPI 
    // C: MPI_Init()
    MPI::Init();
    
    //get a process ID
    // C: MPI_Comm_rank(MPI_COMM_WORLD, &rank)
    rank = MPI::COMM_WORLD.Get_rank();

    cout<<"Hello World! from process "<<rank<<endl;    
    
    //check htop (or similar)
    system("stress --timeout 5s --cpu 1");
    
    //get comunicator size
    //  C: MPI_Comm_size(MPI_COMM_WORLD, &size)
    size = MPI::COMM_WORLD.Get_size();
    
    //close processes
    cout<<"Closing comunicator with "<<size<<" procs"<<endl;
    // C: MPI_Finalize()
    MPI::Finalize();
}