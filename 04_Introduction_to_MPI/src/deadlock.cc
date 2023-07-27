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
       
#ifdef MPI_VERSION
    MPI::Init();
    size = MPI::COMM_WORLD.Get_size();
#endif
    
    char msg[msgsz]  = "Got ball from ";
    char rmsg [msgsz];

    for(int i = 0; i < bounces; i++)
    {
#ifdef MPI_VERSION
        rank = MPI::COMM_WORLD.Get_rank();

        if(rank==0 && size>1)
        {
            MPI::COMM_WORLD.Send(msg, msgsz, MPI_BYTE, 1, 0);
            MPI::COMM_WORLD.Recv(rmsg, msgsz, MPI_BYTE, 1, 1);
        }
    
        if(rank==1 && size>1)
        {
            MPI::COMM_WORLD.Send(msg, msgsz, MPI_BYTE, 0, 1);
            MPI::COMM_WORLD.Recv(rmsg, msgsz, MPI_BYTE, 0, 0);
        }
#endif
        cout << rmsg << rank << endl;
        usleep(1e5);
    }
    
#ifdef MPI_VERSION
    MPI::Finalize();
#endif
}