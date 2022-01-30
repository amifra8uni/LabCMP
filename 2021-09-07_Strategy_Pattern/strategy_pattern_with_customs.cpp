#include "Speed.h"
#include "RungeKutta.h"
#include "Function.h"
#include "SpeedCalculator.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

int main() {

  // Scelgo il metodo di integrazione
  RungeKutta cinteg = RungeKutta();

  // DiffSpeed(nome, beta, massa)
  Function* v = new Speed("vDiff", 0.015, 25.);
  cinteg.setIntegrand( v );

  // Prendo i valori da input
  double t0, t, dt, v0;
  cout << "Program to integrate the l'equazione differenciale della velocitàin un intervallo [t0, t, dt]" << endl;
  cout << "t0: ";
  cin >> t0;
  cout << "t: ";
  cin >> t;
  cout << "intervallo di integrazione" << endl;
  cout << "dt: ";
  cin >> dt;
  cout << "velocità iniziale del corpo: " << endl;
  cin >>  v0;

  // Li passo alle classi
  cinteg.setDt(dt);
  //cout << "Hai impostato come dt: " << dt << endl;

  vector <Speed> allvRK;
  allvRK = cinteg.velocity( t0, v0, t ); // integral from a -> b


  cout << "\t Integral: " << setprecision(6) << sum
  << endl;
  delete v;

  return 0;
}
