/*
This is example demonstrating the basic scalar forward
mode of codipack AD tool.
*/

#include "codi.hpp"
#include <iostream>
using namespace std;

// Step 1: create an implementation of the function with the CoDiPack forward 
// type: RealForward
codi:: RealForward func(const codi::RealForward& x){
    return x*x*x; 
}

int main(int nargs, char** args){

    // Step 2: set the point where the AD will be performed 
    codi::RealForward x = 4.0;

    // Step 3: set the direction of the derivative. Since in this example 
    // the dimension of design variable is 1, this means the derivative we 
    // will evaluate is along the direction of x
    x.setGradient(1.0);

    // Step 4: evaluate the function at given point x, and set the function 
    // value in type: RealForward
    codi::RealForward y = func(x); 

    cout << "f(4.0)= " << y << endl;
    
    // Step 5: using y.GetGradient() to get the derivative of y at point x 
    // along given direction
    cout << "df/dx(4.0)= " << y.getGradient() << endl;
    return 0;
}