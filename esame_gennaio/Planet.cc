// Planet.cc
#include "Planet.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>

using namespace std;

// Costrutttori
Planet::Planet() { // Predefinito
  R_ = 0.;   // radius [km]
  M_ = 0.;   // mass   [kg]
  G_ = 0.;   // costante gravitazionale
  }
Planet::Planet(double radius, double mass, double grav) { // Regolare
  R_ = radius;   // radius
  M_ = mass;     // mass
  G_ = grav;
}
Planet::Planet(const Planet& planet) { // Copia
  R_ = planet.R_;   // radius
  M_ = planet.M_;     // mass
  G_ = planet.G_;
}

// Distruttore
Planet::~Planet() { }

// Metodi di accesso - Getter Methods
double Planet::R() const { return R_; }
double Planet::M() const { return M_; }
double Planet::G() const { return G_; }


// Metodi di aggiornamento - Setter Methods
void Planet::setR(double R) { R_ = R; }
void Planet::setM(double M) { M_ = M; }
void Planet::setG(double G) { G_ = G; }

// Metodi accessori - utility methos
voit print() const {
  cout << "Pianeta (" << R_
       << ", " << M_
       << ", " << G_ << endl;
}
  
