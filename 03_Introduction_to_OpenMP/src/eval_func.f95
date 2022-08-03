module mymodule
    
    contains

    real(8) function eval_func(x)
        real(8), intent(in) :: x

        eval_func = 4.d0/(1.d0 + x * x)
    end function eval_func

end module mymodule