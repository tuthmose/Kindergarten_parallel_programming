program ring
    use mpi
    implicit none

    integer :: rank, error, procs, check, destination, origin
    character(len=40) :: msg, rmsg
    character(len=2) :: s0, s1, s2
    call MPI_Init(error)
    
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, error)    
    call MPI_Comm_size(MPI_COMM_WORLD, procs, error)
    
    check = mod(rank,procs)
        
    if (check.eq.0) then
        destination = 1
        origin      = procs -1
    else if (check.eq.procs-1) then
        destination = 0
        origin      = rank -1
    else
        destination   = check + 1
        origin = check - 1
    endif
    
    write(s0,'(i2)') rank
    write(s1,'(i2)') destination
    write(s2,'(i2)') origin
    msg = s0 // ': sent to ' // s1 // ' and received from ' // s2
    
    if (procs.gt.1) then
        call MPI_Send(msg,40,MPI_BYTE,destination,check,MPI_COMM_WORLD,error)
        call MPI_Recv(rmsg,40,MPI_BYTE,origin,origin,MPI_COMM_WORLD,MPI_STATUS_IGNORE,error)
    endif
    
    write(*,*) rmsg
       
    call MPI_Finalize(error)

end program ring