#include <iostream>
#include <cmath>
#include "codi.hpp"
using namespace std;

// this is used to switch between double and codi datatype
// typedef double MYREAL;
typedef codi::RealForward MYREAL;

// this is the test function
MYREAL myfunc(MYREAL x[]){
    // f = (1-x)^2 + (y-x^2)^2
    return pow((1-x[0]),2) + pow((x[1]-x[0]*x[0]),2);
}

//this is the analytical gradient
void myfunc_grad(MYREAL x[], MYREAL dfdx[]){
    dfdx[0] = 2*(x[0]-1) - 4*x[0]*(x[1]-x[0]*x[0]);
    dfdx[1] = 2*(x[1]-x[0]*x[0]);
}

int main(int argc, char *argv[]){
    // set initial point
    MYREAL x[2] = {2, 3};

    // set finite difference step
    MYREAL dh = 1e-6;
    
    MYREAL x_plus_dx1[2] = {x[0]+dh, x[1]};
    MYREAL x_plus_dx2[2] = {x[0], x[1]+dh};

    // analytical gradient
    MYREAL dfdx[2];
    myfunc_grad(x, dfdx);

    // compute dfdx using FD
    MYREAL dfdx_FD[2]; // dfdx_FD = {dfdx1, dfdx2}
    MYREAL dfdx_FD_err;
    dfdx_FD[0] = (myfunc(x_plus_dx1)-myfunc(x))/dh;
    dfdx_FD[1] = (myfunc(x_plus_dx2)-myfunc(x))/dh;
    dfdx_FD_err = pow((pow((dfdx_FD[0]-dfdx[0]),2)+pow((dfdx_FD[1]-dfdx[1]),2)),0.5);

    // compute dfdx using AD
    MYREAL dfdx_AD[2];
    MYREAL dfdx_AD_err;
    MYREAL* x_AD = x;
    x_AD[0].setGradient(1.0);
    x_AD[1].setGradient(0.0);
    dfdx_AD[0] = myfunc(x_AD).getGradient();
    x_AD[0].setGradient(0.0);
    x_AD[1].setGradient(1.0);
    dfdx_AD[1] = myfunc(x_AD).getGradient();
    dfdx_AD_err = pow((pow((dfdx_AD[0]-dfdx[0]),2)+pow((dfdx_AD[1]-dfdx[1]),2)),0.5);


    // output
    cout << "FD error: " << scientific << dfdx_FD_err << endl;
    cout << "AD error: " << scientific << dfdx_AD_err << endl;
    return 0;
}
