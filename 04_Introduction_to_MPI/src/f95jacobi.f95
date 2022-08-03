 module fjac
 contains
 subroutine jacsolv(kmax,A,b,xold,conv,xnew,order)
 implicit none

 integer :: order
 real(8), dimension(0:order-1,0:order-1) :: A
 real(8), dimension(0:order-1) :: xold,b
 real(8), dimension(0:order-1) :: xnew
 !f2py intent(in)    order
 !f2py intent(out)   xnew
 !f2py depend(order) xnew
 
 integer :: i, k, kmax
 !f2py intent(in,out) kmax
 real(8) :: conv, tol
 !f2py intent(out) conv
 real(8), dimension(0:order-1) :: dd, xtmp
 real(8), dimension(0:order-1, 0:order-1) :: R, D

 conv  = kmax
 tol   = 1e-8

 xtmp = xold
 xnew = 1.
 forall (i=0:size(dd)-1) D(i,i) = A(i,i)
 forall (i=0:size(dd)-1) dd(i)   = 1./A(i,i)
 R = A-D

 do k=1,kmax
     conv = 0.
     do i = 0,order-1
         xnew(i) = (b(i) - DOT_PRODUCT(xtmp,R(i,:)) )*dd(i)
     end do
     conv = SUM((xnew-xtmp)*(xnew-xtmp))

     if (conv <= tol) then
         exit
     end if

     xtmp = xnew

 end do
 
 kmax = k
 
 end subroutine
 end module fjac