/* app.cpp
   File in C++ per l'esame di gennaio 2022 di CMP*/

// Includo gli archivi di intestazione
#include "RungeKutta2.h"
#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "Vector3D.h"
#include "FlySatellite.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {

  // Definisco i miei oggetti

  double MT = 5.972*pow(10,24);
  double RT = 6371*1000;       // m
  double G = 6.67*pow(10,-11); // N m^2/kg^2
  Planet Earth("Earth", RT, MT, G);   // Planet(name, radius, mass, grav const)

  //Atmosphere(double A, double C_d, double F107, double A_p)
  double A = 0;
  double C_d = 2;
  double F107 = 80;
  double A_p = 50;
  Atmosphere aria("Aria", A, C_d, F107, A_p);
  aria.print();

  double r0 = 250; // m
  Vector3D r = Vector3D::Cartesiane(r0, 0 ,0);
  Vector3D v = Vector3D::Cartesiane(0, sqrt(Earth.G()*Earth.M()/r0), 0);
  Satellite sat("Satellite1", r, v, 1200);
  sat.print();

  // Definisco il passo di integrazione
  double dt = 1;

  // Scelgo il mio metodo di integrazione
  return 0;
}
