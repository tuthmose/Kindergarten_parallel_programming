      program simple_pi
      implicit none
      real*8 mysum, x
      integer i, numiter
      character*10 l

      call getarg(1,l)
      read (l,'(I10)') numiter

      mysum = 0.d0

      Do 10 i = 0, numiter-1
        x = (dble(i)+0.5d0)/ dble(numiter)
        mysum = mysum + 4.d0/(x*x + 1.d0)
10    Continue

      write(6,*) mysum / dble(numiter)

      end program simple_pi