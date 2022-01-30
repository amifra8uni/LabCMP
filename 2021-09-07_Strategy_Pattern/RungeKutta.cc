#include "RungeKutta.h"
#include "Speed.h"
//#include <stdlib.h>
#include <iostream>

//#include <time.h>
using std::cout;
using std::endl;

RungeKutta::RungeKutta(double h) : SpeedCalculator() {
    dt_  = h;
}

double RungeKutta::velocity(double t0, double y0, double t) const {
  double y = y0;
  vector <Speed> v;
  for (double i = t0; i < t; i += dt_) {
    
    double K1 = dt_*integrand(y);
    double K2 = dt_*integrand(y+K1*dt_/2.);
    y += K2;
/*cout << "Il tuo passo di integrazione è dt: " << dt_ << endl;
  cout << "sto eseguendo l'integrazione al passo t = " << i << endl;*/
  }
  return y;
}
