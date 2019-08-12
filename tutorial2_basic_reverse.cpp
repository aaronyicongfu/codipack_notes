/*
This is example demonstrating the basic scalar reverse
mode of codipack AD tool.
*/

#include "codi.hpp"
#include <iostream>
using namespace std;

// Step 1: create an implementation of the function with the CoDiPack forward 
// type: RealForward
codi:: RealReverse func(const codi::RealReverse& x){
    return x*x*x;
}

int main(int nargs, char** args){

    // Step 2: define the input variables and 
    // set the point where the AD will be performed
    codi::RealReverse x = 4.0;

    // Step 3: initialize the "tape" used in the reverse AD mode
    codi::RealReverse::TapeType& tape = codi::RealReverse::getGlobalTape();

    // Step 4: activate "tape"
    tape.setActive();

    // Step 5: register input variables into "tape"
    tape.registerInput(x);

    // Step 6: evaluate the function at given point x, and set the function 
    // value in type: RealReverse
    codi::RealReverse y = func(x);

    // Step 7: register output function values into "tape"
    tape.registerOutput(y);

    // Step 8: deactivate "tape", after this no further statements will be recorded
    tape.setPassive(); // tape.setActive()
    
    // Step 9: set the seed value, for 1-dimension function f(x1, x2, x3, ..), just
    // use y.setGradient(1.0)
    y.setGradient(1.0);

    // Step 10: evaluate the tape to get derivatives
    tape.evaluate();

    cout << "f(4.0)= " << y << endl;

    // Step 11: the gradient values can be retrived after the tape has been evaluated
    cout << "df/dx(4.0)= " << x.getGradient() << endl;
    return 0;
}