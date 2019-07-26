#include "codi.hpp"
#include <iostream>
using namespace std;

void func(const codi::RealReverse* x, size_t l, codi::RealReverse* y){
    y[0] = 0.0;
    y[1] = 1.0;
    for (size_t i = 0; i < l; ++i){
        y[0] += x[i];
        y[1] *= x[i];
    }
}

int main(){
    codi::RealReverse x[5];
    codi::RealReverse y[2];
    codi::RealReverse::TapeType& tape = codi::RealReverse::getGlobalTape();
    tape.setActive();
    x[0] = 1.0;
    x[1] = 2.0;
    x[2] = 3.0;
    x[3] = 4.0;
    x[4] = 5.0;
    tape.registerInput(x[0]);
    tape.registerInput(x[1]);
    tape.registerInput(x[2]);
    tape.registerInput(x[3]);
    tape.registerInput(x[4]);
    double jacobian[2][5];
    func(x, 5, y);
    cout << "Jacobian is:" << endl;
    tape.registerOutput(y[0]);
    tape.registerOutput(y[1]);
    tape.setPassive();

    for (int i = 0; i < 2; ++i){
        y[i].setGradient(1.0);
        tape.evaluate();
        for (int j = 0; j < 5; ++j){
            jacobian[i][j] = x[j].getGradient();
            cout << jacobian[i][j] << "  ";
        }
        cout << endl;
        tape.clearAdjoints();
    }

    return 0;
}