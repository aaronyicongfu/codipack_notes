#include <iostream>
#include <complex>
#include "codi.hpp"
using namespace std;

// typedef double TacsScalar;
typedef codi::RealForward TacsScalar;


int main(){
    complex<TacsScalar> c (3.0, 4.0);
    cout << abs(c) << endl;
    return 0;
}