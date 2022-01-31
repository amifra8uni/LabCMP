// app.cpp

// Includo gli archivi di intestazione
#include "RungeKutta2.h"
#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "Vector3D.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {

  // Definisco i miei oggetti
  double MT = 5.972*pow(10,24);
  double RT = 6371;
  double G = 6.67*pow(10,-11); // N m^2/kg^2
  Planet Earth(RT, MT, G);   // Planet(radius, mass)

  double r0 = 250; // m
  Vector 3D r(r0, 0 ,0);
  Vector 3D v(0, sqrt(Earth.G()*Earth.M()/r0), 0);
  Satellite sat(r, v, 1200);

  // Atmosphere(double A, double C_d, double F107, double A_p)
  double A = 0;
  double C_d = 2;
  double F107 = 80;
  double A_p = 50;
  Atmosphere aria(A, C_d, F107, A_p);

  // Definisco il passo di integrazione
  double dt = 1;
  return 0;
}
