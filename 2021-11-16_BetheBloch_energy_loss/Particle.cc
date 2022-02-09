/* Particle.cc
   Implementazione della classe Particle */

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
  p_ = 0.;   // Three momentum in GeV
}
Particle::Particle(double mass, double charge, double threemomentum) { // Regolare
  m_ = mass;            // mass in GeV
  q_ = charge;          // Charge in units of e
  p_ = threemomentum;   // Three momentum
}
Particle::Particle(const Particle& particle) { // Copia
  m_ = particle.m_;   // mass in GeV
  q_ = particle.q_;   // Charge in units of e
  p_ = particle.p_;   // Three momentum
}

// Distruttore
Particle::~Particle() { }

// Metodi di accesso - Getter Methods
double Particle::m() const { return m_; }
double Particle::q() const { return q_; }
double Particle::p() const { return p_; }

// Metodi di aggiornamento - Setter Methods
void Particle::setM(double m) { m_ = m; }
void Particle::setQ(double q) { q_ = q; }
void Particle::setP(double p) { p_ = p; }

// Memeber functions
double Particle::beta() {
  return p_/E();
}

double Particle::gamma() {
  return E()/m_;
}

double Particle::betagamma() {
  return Particle::beta()*Particle::gamma();
}

double Particle::E() {
  return sqrt(m_*m_ + p_*p_);
}
