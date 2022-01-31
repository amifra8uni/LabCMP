// Satellite.cc

#include "Satellite.h"

#include <iostream>
#include <cmath>

using namespace std;

// Costruttore
Satellite::Satellite(Vector3D r, Vector3D v, double m) { // regolare
  r_ = r; // km
  v_ = v; // km/s
  m_ = m; // kg
  cout << "Hai creato Satellite (" << r.print() << " km"
       << ", " << v.print << " km/s"
       << ", " << m << " kg" << endl;
}

// Metodi di accesso - getters
Vector3D Satellite::R() const {return r_}
Vector3D Satellite::V() const {return v_}
double Satellite::M() const {return m_;}

// Metodi di aggiornamento - setters
void Satellite::setX(double x) {r_.setX(x);}
void Satellite::setY(double y) {r_.setY(y);}
void Satellite::setZ(double z) {r_.setZ(z);}
void Satellite::setVx(double vx) {v_.setX(vx);}
void Satellite::setVy(double vy) {v_setY(vy);}
void Satellite::setVz(double vz) {v_.setZ(vz);}
void Satellite::setM(double m)  {m_ = m;}
void Satellite::setR(vector3D r) {r_ = r}
void Satellite::setV(vector3D v) {v_ = v}

// Metodi accessori - utility functions

void Satellite::print() const {
  cout << "Il satellite ha le seguenti propietà\nPosizione: " << r_.print()
       << "velocità" << v_.print()
       << "\nMassa: " << m_ << endl;
}

Vector3D dvdt(Planet plt, Atmosphere atm) {
  Vector3D foo = -plt.G()*plt.M()*r_/(r_.magnitude()*sqrt(r_magnitude())) + atm.D()/m_;
  return foo;
}

Vector3D drdt() {
  return v_;
}
