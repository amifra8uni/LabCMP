// Velocity.cc

#include "Velocity.h"

#include <iostream>

using std::cout;
using std::endl;

Velocity::Velocity(double vx, double vy) {
  vx_=vx;
  vy_=vy;
}

// Metodi di accesso - getters
double Velocity::Vx() const { return vx_; }
double Velocity::Vy() const { return vy_; }

// Metodi di aggiornamento - Getters
void Velocity::setVx(double vx) { vx_=vx; }
void Velocity::setVy(double vy) { vy_=vy; }

void Velocity::print() const {
  cout << "Velocity: (" << vx_ << ", " << vy_ << ")" << endl;
}


// Overloading operators
Velocity Velocity::operator+(const Velocity& rhs) {
  return Velocity( vx_+rhs.vx_, vy_+rhs.vy_);
}
const Velocity& Velocity::operator=(const Velocity& rhs) {
  vx_ = rhs.vx_;
  vy_ = rhs.vy_;

  return *this;
}
