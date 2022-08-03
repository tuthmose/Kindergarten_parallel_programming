program integral
    use mymodule
    implicit none

    integer :: num_steps, num_threads
    real(8) :: first, last, dx, t0, t1, PI
       
    external omp_get_wtime, omp_get_num_threads
    real(8) :: omp_get_wtime
    integer :: omp_get_num_threads

    first = 0.d0
    last  = 1.d0
    PI    = 0.d0
    num_steps = 1e8
    dx = (last-first)/num_steps
       
    t0 = omp_get_wtime();
    !$OMP parallel 
        num_threads = omp_get_num_threads()
        !$OMP Atomic
        PI = PI + midrect(first ,dx, num_steps, num_threads)
    !$OMP end parallel
    
    PI = PI * dx
    t1 = omp_get_wtime();
    
    write(6,*) 'Loop completed in ',1000.d0*(t1-t0),' ms'
    write(6,*) 'Integral value ', PI
    
    contains
    
    real(8) function midrect(first, dx, num_steps, num_threads)
    
        real(8), intent(in) :: first, dx
        integer, intent(in) :: num_steps, num_threads

        external omp_get_thread_num
        real(8) :: mid_x, mid_y
        integer :: thread_id, i, omp_get_thread_num
        
        thread_id = omp_get_thread_num() 
        midrect = 0.d0
        
        do 10 i = thread_id, num_steps, num_threads
            mid_x = first + i * dx
            mid_y = eval_func(mid_x)
            midrect = midrect + mid_y
10      continue        

    end function midrect
        
end program integral