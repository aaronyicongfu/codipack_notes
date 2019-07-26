#include "codi.hpp"
#include <iostream>
using namespace std;

void func(const codi::RealForward* x, size_t l, codi::RealForward* y){
    y[0] = 0.0;
    y[1] = 1.0;
    for (size_t i = 0; i < l; ++i){
        y[0] += x[i];
        y[1] *= x[i];
    }
}

int main(){
    codi::RealForward x[5];
    codi::RealForward y[2];
    x[0] = 1.0;
    x[1] = 2.0;
    x[2] = 3.0;
    x[3] = 4.0;
    x[4] = 5.0;
    double jacobian[2][5];
    cout << "Transposd Jacobian is:" << endl;
    for (size_t i = 0; i < 5; ++i){
        x[i].setGradient(1.0);
        func(x, 5, y);
        jacobian[0][i] = y[0].getGradient();
        jacobian[1][i] = y[1].getGradient();
        cout << jacobian[0][i] << "  " << jacobian[1][i] << endl;
        x[i].setGradient(0.0);
    }
    
    return 0;
}
