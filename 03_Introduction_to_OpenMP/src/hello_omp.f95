program hello

    external omp_get_thread_num, omp_get_wtime
    integer:: omp_get_thread_num
    real(8):: omp_get_wtime
            
    !$OMP parallel
        write(6,*) 'Hello World ! from thread ', omp_get_thread_num(),' at time ',omp_get_wtime()
    !$OMP end parallel
        
end program hello        