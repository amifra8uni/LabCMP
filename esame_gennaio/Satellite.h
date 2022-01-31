// Satellite.h

#ifndef Satellite_h
#define Satellite_h

#include "Vector3D.h"
#include "Atmosphere.h"
#include "Planet.h"

class Satellite {
  
 public:
  // Costruttori
  Satellite(Vector3D r, Vector3D v, double m); // Regolare

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
  Vector3D dvdt(Planet plt, Atmosphere atm);
  Vector3D drdt();

 private:
  Vector3D r_;
  Vector3D v_;
  double m_;  
};
#endif
