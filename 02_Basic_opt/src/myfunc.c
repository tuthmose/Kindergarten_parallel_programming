#include "integral.h"

#ifndef novec
#pragma omp declare simd
#endif
double myfunc(const double x)
{
  return 1./x;
}