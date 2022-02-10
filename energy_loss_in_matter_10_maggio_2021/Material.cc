/* Material.cc
   Implementazione della classe Material 
   Francesco Amicucci 1795152 */

// Includo l'archivio d'intestazione della classe
#include "Material.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>

using namespace std;

// Costrutttori
Material::Material() { // Predefinito
  rho_ = 0.;   // Density in g/cm^3
  A_ = 0.;     // Atomic mass
  Z_ = 0.;     // charge in units of e
  I_ = 0.;     // mean ionisation energy in eV
  X_0_ = 0.;   // Lunghezza di radiazione in cm
  delta_ = 0.; // correzione di densità
  E_c_ = 0.;   // energia critica del mezzo in MeV
  }
Material::Material(double density, double atomicMass, double charge, double ionisation,  double lung_rad, double delta, double e_critica) { // Regolare
  rho_ = density;      // Density in g/cm^3
  A_ = atomicMass;     // Atomic mass
  Z_ = charge;         // charge in units of e
  I_ = ionisation;     // mean ionisation energy in eV
  X_0_ = lung_rad;     // Lunghezza di radiazione in cm
  delta_ = delta;      // correzione di densità
  E_c_ = e_critica;    // energia critica del mezzo in MeV
  srand48(time(0));
}
Material::Material(const Material& material) { // Copia
  rho_   = material.rho_;   // Density in g/cm^3
  A_     = material.A_;     // Atomic mass
  Z_     = material.Z_;     // charge in units of e
  I_     = material.I_;     // mean ionisation energy in eV
  X_0_   = material.X_0_;   // Lunghezza di radiazione in cm
  delta_ = material.delta_; // correzione di densità
  E_c_   = material.E_c_;    // energia critica del mezzo in MeV
}

// Distruttore
Material::~Material() { }

// Metodi di accesso - Getter Methods
double Material::rho()   const { return rho_; }
double Material::A()     const { return A_; }
double Material::Z()     const { return Z_; }
double Material::I()     const { return I_; }
double Material::X_0()   const { return X_0_; }
double Material::delta() const { return delta_; }
double Material::E_c()   const { return E_c_; }

// Metodi di aggiornamento - Setter Methods
void Material::setRho(double rho) { rho_ = rho; }
void Material::setA(double A) { A_ = A; }
void Material::setZ(double Z) { Z_ = Z; }
void Material::setI(double I) { I_ = I; }
void Material::setX_0(double X_0) { X_0_ = X_0; }
void Material::setDelta(double delta) { delta_ = delta; }
void Material::setE_c(double E_c) { E_c_ = E_c; }

// Memeber functions
double Material::dE(Particle& particle, double dx, double res, TRandom* gen, double E0, double x) {
  double perdita;  // in MeV

  if ( particle.E() < E_c_) {
    double K = 0.307075;     // MeV cm^2/mol
    double me = 510999;      // eV
    double perdita_media = dx*rho_*K*particle.q()*particle.q()*Z_*( log(2*me*particle.betagamma()*particle.betagamma()/I_)-0.5*particle.beta()*particle.beta() - 0.25*delta_)/(A_*particle.beta()*particle.beta());
    perdita = gen->Gaus(perdita_media, perdita_media*res);
    // cout << "Ho fatto BB a x = " << x << " cm" <<endl; per controllo
  }
  else {
    double evento = (double) lrand48() / RAND_MAX;
    if (evento < prob_Brems(x)) perdita = 0.;
    else perdita = particle.E()*(1-prob_Brems(dx));
  }

  return perdita; // In MeV
}

double Material::prob_Brems(double x) {
  return exp(-x/X_0_);
}

// Info
void Material::print() const {
  cout << "Il materiale ha le seguenti propietà:\nDensità: "<< rho_ << "\nMassa Atomica: "<< A_ << "\nNumero atomico: "<< Z_ << "\nPotenziale di ionizzazione: "<< I_ << "\nLunghezza di radiazione: " << X_0_ << "\nCorrezione di densità: " << delta_ << "\nEnergia Critica: "<< E_c_ <<" MeV\n" << endl;
}
