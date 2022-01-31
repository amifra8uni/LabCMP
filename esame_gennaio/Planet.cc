/* Planet.cc
   Implementazione della classe Planet*/

#include "Planet.h"

// Tutti gli archivi aggiiuntivi sono in Planet.h

// Costrutttori
Planet::Planet() { // Predefinito
  name_ = "Planet";
  R_ = 0.;   // radius [km]
  M_ = 0.;   // mass   [kg]
  G_ = 0.;   // costante gravitazionale [N*m^2/kg^2]
}
Planet::Planet(const string& name, double radius, double mass, double grav) { // Regolare
  name_ = name;
  R_ = radius;   // radius
  M_ = mass;     // mass
  G_ = grav;
  cout << "Pianeta (" << name_
       << ", " << R_ << " m"
       << ", " << M_ << " kg"
       << ", " << G_ << " N*m^2/kg^2) "<<endl;
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
void Planet::print() const {
  cout << "Pianeta (" << R_ << " m"
       << ", " << M_ << " kg"
       << ", " << G_ << "N*m^2/kg^2) "<<endl;
}
  
