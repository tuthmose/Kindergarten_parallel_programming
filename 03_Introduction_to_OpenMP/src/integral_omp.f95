program integral
    use mymodule
    implicit none

    integer :: num_steps, num_threads, i
    real(8) :: first, last, dx, t0, t1, PI
    real(8), dimension(:), allocatable :: myInt
    
    external omp_get_wtime, omp_get_num_threads
    real(8) :: omp_get_wtime
    integer :: omp_get_num_threads

    first = 0.d0
    last  = 1.d0
    PI    = 0.d0
    num_steps = 1e8
    dx = (last-first)/num_steps
    
    !$OMP parallel 
        num_threads = omp_get_num_threads()
    !$OMP end parallel
    allocate (myInt(num_threads))
    
    t0 = omp_get_wtime();
    !$OMP parallel 
        call midrect(myInt, first ,dx, num_steps, num_threads)           
    !$OMP end parallel
    
    do 10 i = 1, num_threads
10      PI = PI + myInt(i)    
    PI = PI * dx
    t1 = omp_get_wtime();
    
    write(6,*) 'Loop completed in ',1000.d0*(t1-t0),' ms'
    write(6,*) 'Integral value ', PI
    
    contains
    
    subroutine midrect(myInt, first, dx, num_steps, num_threads)
    
        real(8), intent(in) :: first, dx
        real(8), dimension (*), intent(inout) :: myInt
        integer, intent(in) :: num_steps, num_threads

        external omp_get_thread_num
        real(8) :: mid_x, mid_y
        integer :: thread_id, i, omp_get_thread_num
        
        thread_id = omp_get_thread_num() 
        
        do 10 i = thread_id, num_steps-1, num_threads
            mid_x = first + dble(i) * dx
            mid_y = eval_func(mid_x)
            myInt(thread_id+1) = myInt(thread_id+1) + mid_y
10      continue        

    end subroutine    
    
end program integral