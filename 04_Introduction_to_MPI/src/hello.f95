program hello
    use mpi
    implicit none

    integer :: rank, procs, ierr
    
    rank  = 0
    procs = 0

    !start MPI 
    call MPI_Init(ierr)
    
    !Get a process ID
    call MPI_Comm_rank(MPI_COMM_WORLD, rank, ierr)
    write(*,*) 'Hello World! from process ', rank
    
    !check htop (or similar); only with std=gnu
    call EXECUTE_COMMAND_LINE('stress --timeout 10s --cpu 1')
    
    !Get number of procs
    call MPI_Comm_size(MPI_COMM_WORLD, procs, ierr)
    
    !close processes
    write(*,*) 'Closing MPI context with ',procs,' processes'
    call MPI_Finalize(ierr)
    
end program hello