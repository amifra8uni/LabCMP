// Satellite.h

#ifndef Satellite_h
#define Satellite_h

#include "Vector3D.h"
#include "Atmosphere.h"
#include "Planet.h"

#include <iostream>
#include <cmath>

using namespace std;

class Satellite {
  
 public:
  // Costruttori
  Satellite(const string& name, Vector3D r, Vector3D v, double m); // Regolare

// Metodi di accesso - getters
  Vector3D R() const;
  Vector3D V() const; 
  double M() const;

// Metodi di aggiornamento - setters
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setVx(double vx);
  void setVy(double vy);
  void setVz(double vz); 
  void setM(double m);
  void setR(Vector3D r);
  void setV(Vector3D v);

// Metodi accessori - utility functions
  
  void print() const;

 private:
  string name_;
  Vector3D r_;
  Vector3D v_;
  double m_;  
};
#endif
