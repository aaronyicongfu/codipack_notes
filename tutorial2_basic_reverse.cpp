#include "codi.hpp"
#include <iostream>
using namespace std;

codi:: RealReverse func(const codi::RealReverse& x){
    return x*x*x;
}

int main(){
    codi::RealReverse x = 4;
    codi::RealReverse::TapeType& tape = codi::RealReverse::getGlobalTape();
    tape.setActive();
    tape.registerInput(x);
    codi::RealReverse y = func(x);
    tape.registerOutput(y);
    tape.setPassive();
    y.setGradient(1.0);
    tape.evaluate();

    cout << "f(4.0)= " << y << endl;
    cout << "df/dx(4.0)= " << x.getGradient() << endl;
    return 0;
}