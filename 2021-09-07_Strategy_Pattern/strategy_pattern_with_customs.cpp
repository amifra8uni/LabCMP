#include "DiffSpeed.h"
#include "RungeKutta.h"
#include "Function.h"
#include "SpeedCalculator.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {

  RungeKutta cinteg = RungeKutta();
  Function*  g1 = new DiffSpeed("v1", 0.015, 25.);
  cinteg.setIntegrand( g1 );

  double t0, t, dt;
  cout << "Program to integrate the l'equazione differenciale della velocitàin un intervallo [t0, t, dt]" << endl;
  cout << "t0: ";
  cin >> t0;
  cout << "t: ";
  cin >> t;
  cout << "intervallo di integrazione" << endl;
  cout << "dt: ";
  cin >> dt;
  cinteg.setDt(dt);
  cout << "Hai impostato come dt: " << dt << endl;
  double sum = cinteg.velocity( t0, 15., t ); // integral from a -> b
  cout << "\t Integral: " << setprecision(6) << sum
  << endl;
  delete g1;

  return 0;
}
