// Satellite.cc

#include "Satellite.h"

// Costruttore
Satellite::Satellite() {
  name_ = "Nessuno";
  r_ = Vector3D::Cartesiane(0,0,0);
  v_ = Vector3D::Cartesiane(0,0,0);
  m_ = 0.;
}
Satellite::Satellite(const string& name, Vector3D r, Vector3D v, double m) { // regolare
  name_ = name;
  r_ = r; // m
  v_ = v; // m/s
  m_ = m; // kg
  cout << "Hai creato un satellite " << name_
       << " con Posizione: ";
  r_.print();
  cout << "Velocita' :";
  v_.print();
}
Satellite::Satellite(const Satellite& satellite) {
  name_ = satellite.name_;
  r_ = satellite.r_; // m
  v_ = satellite.v_; // m/s
  m_ = satellite.m_; // kg
}

// Metodi di accesso - getters
Vector3D Satellite::R() const {return r_;}
Vector3D Satellite::V() const {return v_;}
double Satellite::M() const {return m_;}

// Metodi di aggiornamento - setters
void Satellite::setX(double x) {r_.setX(x);}
void Satellite::setY(double y) {r_.setY(y);}
void Satellite::setZ(double z) {r_.setZ(z);}
void Satellite::setVx(double vx) {v_.setX(vx);}
void Satellite::setVy(double vy) {v_.setY(vy);}
void Satellite::setVz(double vz) {v_.setZ(vz);}
void Satellite::setM(double m)  {m_ = m;}
void Satellite::setR(Vector3D r) {r_ = r;}
void Satellite::setV(Vector3D v) {v_ = v;}

// Metodi accessori - utility functions

void Satellite::print() const {
  cout << "Info sul satellite (" << name_
       << ", " << m_ << " kg)" << endl;
}
