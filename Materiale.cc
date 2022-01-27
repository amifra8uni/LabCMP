/* Materiale.cc
   Implementazione della classe Material */

// Includo l'archivio d'intestazione della classe
#include "Materiale.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>

using namespace std;


// Costrutttori
Materiale::Materiale() { // Predefinito
  rho_ = 0.;   // Density in g/cm^3
  A_ = 0.;     // Atomic mass
  Z_ = 0.;     // charge in units of e
  I_ = 0.;     // mean ionisation energy in eV
  X_0_ = 0.;   // Lunghezza di radiazione in cm
  delta_ = 0.; // correzione di densità
  E_c_ = 0.;   // energia critica del mezzo in MeV
  }
Materiale::Materiale(double density, double atomicMass, double charge, double ionisation,  double lung_rad, double delta, double e_critica) { // Regolare
  rho_ = density;      // Density in g/cm^3
  A_ = atomicMass;     // Atomic mass
  Z_ = charge;         // charge in units of e
  I_ = ionisation;     // mean ionisation energy in eV
  X_0_ = lung_rad;     // Lunghezza di radiazione in cm
  delta_ = delta;      // correzione di densità
  E_c_ = e_critica;    // energia critica del mezzo in MeV
}
Materiale::Materiale(const Materiale& material) { // Copia
  rho_   = material.rho_;   // Density in g/cm^3
  A_     = material.A_;     // Atomic mass
  Z_     = material.Z_;     // charge in units of e
  I_     = material.I_;     // mean ionisation energy in eV
  X_0_   = material.X_0_;   // Lunghezza di radiazione in cm
  delta_ = material.delta_; // correzione di densità
  E_c_   = material.E_c_;    // energia critica del mezzo in MeV
}

// Distruttore
Materiale::~Materiale() { }

// Metodi di accesso - Getter Methods
double Materiale::rho()   const { return rho_; }
double Materiale::A()     const { return A_; }
double Materiale::Z()     const { return Z_; }
double Materiale::I()     const { return I_; }
double Materiale::X_0()   const { return X_0_; }
double Materiale::delta() const { return delta_; }
double Materiale::E_c()   const { return E_c_; }

// Metodi di aggiornamento - Setter Methods
void Materiale::setRho(double rho) { rho_ = rho; }
void Materiale::setA(double A) { A_ = A; }
void Materiale::setZ(double Z) { Z_ = Z; }
void Materiale::setI(double I) { I_ = I; }
void Materiale::setX_0(double X_0) { X_0_ = X_0; }
void Materiale::setDelta(double delta) { delta_ = delta; }
void Materiale::setE_c(double E_c) { E_c_ = E_c; }

// Memeber functions
double Materiale::dE(Particella& particle, double dx, double res, TRandom* gen) {
  double perdita;  // in MeV

  if ( particle.E() < E_c_) {
    double K = 0.307075;     // MeV cm^2/mol
    double me = 510999;      // eV
    double perdita_media =  rho_*K*particle.q()*particle.q()*Z_*( log(2*me*particle.betagamma()*particle.betagamma()/I_)-particle.beta()*particle.beta() - delta_/2)*dx;
    perdita = gen->Gaus(perdita_media, perdita_media*res);
  }
  else {
    double evento = (double) lrand48() / RAND_MAX;
    if (evento < prob_Brems(dx)) perdita = 0.;
    else perdita = particle.E()*(1-prob_Brems(dx));
  }

  return perdita; // In MeV
}

double Materiale::prob_Brems(double dx) {
  return exp(-dx/X_0_);
}

// Info
void Materiale::print() const {
  cout << "Il materiale ha le seguenti propietà:\nDensità: "<< rho_ << "\nMassa Atomica: "<< A_ << "\nNumero atomico: "<< Z_ << "\nPotenziale di ionizzazione: "<< I_ << "\nLunghezza di radiazione: " << X_0_ << "\nCorrezione di densità: " << delta_ << "\nEnergia Critica: "<< E_c_ <<" MeV\n" << endl;
}
