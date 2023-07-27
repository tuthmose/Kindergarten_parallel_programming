program integral
    use mymodule
    implicit none

    integer :: num_steps, i
    real(8) :: first, last, dx
    real(8) :: myInt, mid_x, mid_y, t0, t1
    
    external omp_get_wtime
    real(8)  omp_get_wtime

    first = 0.d0
    last  = 1.d0
    myInt = 0.d0
    num_steps = 1e8
    dx = (last-first)/num_steps

    t0 = omp_get_wtime();
    do i = 1,num_steps
        
        mid_x = first + i * dx
        mid_y = eval_func(mid_x)
        myInt = myInt + mid_y
        
    end do
    myInt = myInt*dx
    t1 = omp_get_wtime();
    
    write(6,*) 'Loop completed in ',1000.d0*(t1-t0),' ms'
    write(6,*) 'Integral value ', myInt
    
end program integral