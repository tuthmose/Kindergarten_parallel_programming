import numpy as np
import swigmc

npoints = int(1e7)
x = 2.*np.random.rand(npoints)-1
y = 2.*np.random.rand(npoints)-1
print(x[0],y[0])

pi = swigmc.swigpi(x,y)
print(pi)