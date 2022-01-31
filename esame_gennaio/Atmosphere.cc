// Atmosphere.cc
#include "Atmosphere.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Costrutttori
Atmosphere::Atmosphere() { // Predefinito
  A_ = 0.;   // cross sectional area [m^2]
  C_d_ = 0.; // Drag coefficient [none]
  F107_ = 0.;// solar activity [SFUs]
  A_p_ = 0.; // geomagnatica index [none]
}
Atmosphere::Atmosphere(double A, double C_d, double F107, double A_p) { // Predefinito
  A_ = A;      // cross sectional area [m^2]
  C_d_ = C_d;  // Drag coefficient [none]
  F107_ = F107;// solar activity [SFUs]
  A_p_ = A_p;  // geomagnatica index [none]
}
Atmosphere::Atmosphere(const Atmosphere& atm) { // Copia
  A_ = atm.A_;      // cross sectional area [m^2]
  C_d_ = atm.C_d_;  // Drag coefficient [none]
  F107_ = atm.F107_;// solar activity [SFUs]
  A_p_ = atm.A_p_;  // geomagnatica index [none]
}

// Distruttore
Atmosphere::~Atmosphere() { }

// Metodi di accesso - Getter Methods
double Atmosphere::A() const { return A_; }
double Atmosphere::C_d() const { return C_d_; }
double Atmosphere::F107() const { return F107_; }
double Atmosphere::A_p() const { return A_p_; }

// Metodi di aggiornamento - Setter Methods
void Atmosphere::setA(double A) { A_ = A; }
void Atmosphere::setC_d(double C_d) { C_d_ = C_d; }
void Atmosphere::setF107(double F107) { F107_ = F107; }
void Atmosphere::setA_p(double A_p) { A_p_ = A_p; }

// Memeber functions

double Atmosphere::T() { // Temperatura
  return 900 + 2.5*(F107_-70)+1.5*A_p_;
}

double Atmosphere::mu(double h) { // molecular mass of the air
  return 27 - 0.012*(h - 200);
}

double Atmosphere::rho(double h) { // density of the air
  return 6*pow(10, -10)*exp(-(h-175)*Atmosphere::mu(h)/Atmosphere::T()); // [Kg/m^3]
}

// Drag force: dal momento che è parallelo alla velocità, lo tratto come uno scalare
double Atmosphere::D(double v, double h) {
  return -0.5*Atmosphere::rho(h)*v*v*A_*C_d_;
}

// Metodi accessori - Utility Methods
void print() const {
  cout << "Atmosphera (" << A_
       << ", " << C_d_
       << ", " << F107_
       << ", " << A_p << endl;
}
