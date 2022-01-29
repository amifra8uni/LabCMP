/* Material.cc
   Implementazione della classe Material */

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
  }
Material::Material(double density, double atomicMass, double charge, double ionisation) { // Regolare
  rho_ = density;      // Density in g/cm^3
  A_ = atomicMass;     // Atomic mass
  Z_ = charge;         // charge in units of e
  I_ = ionisation;     // mean ionisation energy in eV
}
Material::Material(const Material& material) { // Copia
  rho_ = material.rho_;   // Density in g/cm^3
  A_   = material.A_;     // Atomic mass
  Z_   = material.Z_;     // charge in units of e
  I_   = material.I_;     // mean ionisation energy in eV
}

// Distruttore
Material::~Material() { }

// Metodi di accesso - Getter Methods
double Material::rho() const { return rho_; }
double Material::A() const { return A_; }
double Material::Z() const { return Z_; }
double Material::I() const { return I_; }

// Metodi di aggiornamento - Setter Methods
void Material::setRho(double rho) { rho_ = rho; }
void Material::setA(double A) { A_ = A; }
void Material::setZ(double Z) { Z_ = Z; }
void Material::setI(double I) { I_ = I; }

// Memeber functions
double Material::dEdx(Particle& particle, double delta) {
  /* La condizione da verificare è
     K =  sqrt(p^2 + m^2) - m < X = 50 MeV
     per evitare di usare la radice useremo
     E^2 = p^2 + m^2 < (X + m)^2 */
  double E2, soglia, perdita;  // in MeV/cm
  E2 = particle.p()*particle.p() + particle.m()*particle.m();
  soglia = (0.05 + particle.m())*(0.05 + particle.m());

  if ( E2 > soglia) {
    double K = 0.307075;     // MeV cm^2/mol
    double me = 510999;      // eV
    perdita =  rho_*K*particle.q()*particle.q()*Z_*( log(2*me*particle.betagamma()*particle.betagamma()/I_)-particle.beta()*particle.beta() - delta/2);
  }
  else perdita = rho_*2./(particle.betagamma()*particle.betagamma());

  return perdita/1000; // In GeV
}
