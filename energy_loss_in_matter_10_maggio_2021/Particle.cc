/* Particle.cc
   Implementazione della classe Particle
   Esame 10 maggio 2021 - Francesco Amicucci 1795152 */

// Includo l'archivio d'intestazione della classe
#include "Particle.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>

using namespace std;

// Costrutttori
Particle::Particle() { // Predefinito
  m_ = 0.;   // mass in GeV
  q_ = 0.;   // Charge in units of e
  E_ = 0.;   // Three momentum in GeV
}
Particle::Particle(double mass, double charge, double energy) { // Regolare
  m_ = mass;            // mass in GeV
  q_ = charge;          // Charge in units of e
  E_ = energy;   // Three momentum
}
Particle::Particle(const Particle& particle) { // Copia
  m_ = particle.m_;   // mass in GeV
  q_ = particle.q_;   // Charge in units of e
  E_ = particle.E_;   // Three momentum
}

// Distruttore
Particle::~Particle() { }

// Metodi di accesso - Getter Methods
double Particle::m() const { return m_; }
double Particle::q() const { return q_; }
double Particle::E() const { return E_; }

// Metodi di aggiornamento - Setter Methods
void Particle::setM(double m) { m_ = m; }
void Particle::setQ(double q) { q_ = q; }
void Particle::setE(double E) { E_ = E; }

// Memeber functions

double Particle::K() {
  return E_ - m_;
}

double Particle::beta() {
  double p = sqrt(E_*E_-m_*m_);
  return p/E_;
}

double Particle::gamma() {
  return E_/m_;
}

double Particle::betagamma() {
  return Particle::beta()*Particle::gamma();
}

void Particle::print() const {
  cout << "La particella ha le seguenti propieta'\nMassa: " << m_ << " MeV" << "\nCarica: " << q_ << "\nEnergia " << E_ << " MeV\n" << endl;
}
