#include "codi.hpp"
#include <iostream>
using namespace std;

// same function as tutorial 3 and 4 but in template form
template<typename Real>
void func(const Real* x, size_t l, Real* y){
    y[0] = 0.0;
    y[1] = 1.0;
    for (size_t i = 0; i < l; ++i){
        y[0] += x[i];
        y[1] *= x[i];
    }
}

int main(){
    // Forward Mode
    codi::RealForwardVec<5> x[5];  // <5> means there are 5 seeds (dx1, dx2, .., dx5)
    codi::RealForwardVec<5> y[2];
    x[0] = 1.0;
    x[1] = 2.0;
    x[2] = 3.0;
    x[3] = 4.0;
    x[4] = 5.0;
    double jacobian[2][5];    
    cout << "(Forward mode) Transposd Jacobian is:" << endl;
    for (int i = 0; i < 5; ++i){
        x[i].gradient()[i] = 1.0;
    }
    func(x, 5, y);
    for (int i = 0; i < 5; ++i){
        jacobian[0][i] = y[0].getGradient()[i];
        jacobian[1][i] = y[1].getGradient()[i];
        cout << jacobian[0][i] << "  " << jacobian[1][i] << endl;
    }

    //Reverse Mode
    codi::RealReverseVec<2> xR[5];  // <2> means there are 2 seeds (dy1, dy2)
    codi::RealReverseVec<2> yR[2];
    codi::RealReverseVec<2>::TapeType& tape = codi::RealReverseVec<2>::getGlobalTape();
    tape.setActive();
    xR[0] = 1.0;
    xR[1] = 2.0;
    xR[2] = 3.0;
    xR[3] = 4.0;
    xR[4] = 5.0;
    tape.registerInput(xR[0]);
    tape.registerInput(xR[1]);
    tape.registerInput(xR[2]);
    tape.registerInput(xR[3]);
    tape.registerInput(xR[4]);
    double jacobianR[2][5]; 
    func(xR, 5, yR);
    cout << "(Reversr mode) Jacobian is:" << endl;
    tape.registerOutput(yR[0]);
    tape.registerOutput(yR[1]);
    tape.setPassive();

    for (int i = 0; i < 2; ++i){
        yR[i].gradient()[i] = 1;
        tape.evaluate();
        for (int j = 0; j < 5; ++j){
            jacobianR[i][j] = xR[j].getGradient()[i];
            cout << jacobianR[i][j] << "  ";
        }
        cout << endl;
    }
    return 0;
}
