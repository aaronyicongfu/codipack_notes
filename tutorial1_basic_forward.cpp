#include "codi.hpp"
#include <iostream>
using namespace std;

// define the function to be differentiation with 
// CoDiPack forward type: RealForward in namespace codi.
codi:: RealForward func(const codi::RealForward& x){
    return x*x*x; 
}

int main(int nargs, char** args){
    codi::RealForward x = 4.0;
    x.setGradient(1.0);
    codi::RealForward y = func(x);  // call func to return y in RealForward type

    cout << "f(4.0)= " << y << endl;
    cout << "df/dx(4.0)= " << y.getGradient() << endl;
    return 0;
}