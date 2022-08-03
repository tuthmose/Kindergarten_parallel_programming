#include <iostream>
#include <fstream>
#include <new>

using namespace std;

int main()
{
    double H0 = 100., H1 = 100.;   //temperature at boundaries

    int Ncell = 5e2; //number of cells along x
    int Nstep = 1e6; //number of time steps
    
    double delta_t, delta_x, scalef; // spacing in time and space
    delta_t = 1. / ((double ) Nstep);
    delta_x = 1. / ((double ) Ncell);
    scalef = delta_t / (delta_x * delta_x);
    
    double *Temp, *Tnew, *swap;
    Temp = new double [Ncell]; // set array to zero
    Tnew = new double [Ncell]; // alg. does not involve middle time steps
    
    Temp[0] = H0;
    Temp[Ncell-1] = H1;
    Tnew[0] = H0;
    Tnew[Ncell-1] = H1;
    
    for(int time = 0; time < Nstep; time++)     // loop on time steps
    {
        //apply stencil
        #pragma omp simd
        for(int cell = 1; cell < Ncell-1; cell++) // loop on spatial domain
            // central 2nd ord finite difference
            Tnew[cell] = Temp[cell] + scalef * (Temp[cell+1] - 2.*Temp[cell] + Temp[cell-1]);
        
        //avoid to use array buffer
        swap = Tnew;
        Tnew = Temp;
        Temp = swap;
    }
    
    ofstream outfile;
    outfile.open ("temp_field.dat");
    for(int i=1; i < Ncell-1; i++)
        outfile << i << " " << Tnew[i] << endl;
    outfile.close();
    return 0;
}