/* Particella.cc
   Implementazione della classe Particella */

// Includo l'archivio d'intestazione della classe
#include "Particella.h"

// Incluso tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>

using namespace std;

// Costrutttori
Particella::Particella() { // Predefinito
  m_ = 0.;   // mass in GeV
  q_ = 0.;   // Charge in units of e
  E_ = 0.;   // Three momentum in GeV
}
Particella::Particella(double mass, double charge, double energy) { // Regolare
  m_ = mass;            // mass in GeV
  q_ = charge;          // Charge in units of e
  E_ = energy;   // Three momentum
}
Particella::Particella(const Particella& particle) { // Copia
  m_ = particle.m_;   // mass in GeV
  q_ = particle.q_;   // Charge in units of e
  E_ = particle.E_;   // Three momentum
}

// Distruttore
Particella::~Particella() { }

// Metodi di accesso - Getter Methods
double Particella::m() const { return m_; }
double Particella::q() const { return q_; }
double Particella::E() const { return E_; }

// Metodi di aggiornamento - Setter Methods
void Particella::setM(double m) { m_ = m; }
void Particella::setQ(double q) { q_ = q; }
void Particella::setE(double E) { E_ = E; }

// Memeber functions

double Particella::K() {
  return E_ - m_;
}

double Particella::beta() {
  double p = sqrt(E_*E_-m_*m_);
  return p/E_;
}

double Particella::gamma() {
  double p = sqrt(E_*E_-m_*m_);
  return E_/m_;
}

double Particella::betagamma() {
  return Particella::beta()*Particella::gamma();
}

void Particella::print() const {
  cout << "La particella ha le seguenti propietà\nMassa: " << m_ << " MeV" << "\nCarica: " << q_ << "\nEnergia " << E_ << " MeV\n" << endl;
}
