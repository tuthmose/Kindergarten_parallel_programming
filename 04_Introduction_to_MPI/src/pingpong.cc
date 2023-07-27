#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <unistd.h>

using namespace std;
#define msgsz 4096

int main()
{
    int rank, size;
    const int bounces = 6;
       
    MPI::Init();
    size = MPI::COMM_WORLD.Get_size();
    
    char msg[msgsz]  = "Got ball from ";
    char rmsg [msgsz];

    for(int i = 0; i < bounces; i++)
    {
        rank = MPI::COMM_WORLD.Get_rank();
        if(rank==0 && size>1)
        {
            //C: MPI_Send(msg, msgsz, MPI_BYTE, 1, 0, MPI_COMM_WORLD)
            MPI::COMM_WORLD.Send(msg, msgsz, MPI_BYTE, 1, 0);
            
            //C: MPI_Recv(msg, msgsz, MPI_BYTE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE)
            MPI::COMM_WORLD.Recv(rmsg, msgsz, MPI_BYTE, 1, 1);            
        }
    
        if(rank==1 && size>1)
        {           
            MPI::COMM_WORLD.Recv(rmsg, msgsz, MPI_BYTE, 0, 0);
            MPI::COMM_WORLD.Send(msg, msgsz, MPI_BYTE, 0, 1);
        }
        cout << rmsg << rank << endl;
        usleep(5e5);
    }
    MPI::Finalize();
    return 0;
}