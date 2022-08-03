program pingpong
    use mpi
    implicit none

    integer :: i, rank, size, error, bounces
    character(len=14) :: msg, rmsg
    
    rank  = 0
    bounces = 6
    msg  = 'Got ball from '

    call MPI_Init(error)
    
    do 10 i = 1, bounces
    
        call MPI_Comm_rank(MPI_COMM_WORLD, rank, error)    
        call MPI_Comm_size(MPI_COMM_WORLD, size, error)  
        
        if(size.gt.1) then
            if (rank.eq.0) then
                call MPI_Send(msg, 15, MPI_BYTE, 1, 0, MPI_COMM_WORLD, error)
                call MPI_Recv(rmsg, 15, MPI_BYTE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE, error)
            endif

            if(size.gt.1.and.rank.eq.1) then
                call MPI_Recv(rmsg, 15, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE, error)
                call MPI_Send(msg, 15, MPI_BYTE, 0, 1, MPI_COMM_WORLD, error)
            endif
        endif
        write(*,*) rmsg, rank
        call EXECUTE_COMMAND_LINE('sleep 1')
    
10  continue    
    
    call MPI_Finalize(error)

end program pingpong