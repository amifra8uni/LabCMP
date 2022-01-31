// Atmosphere.h

#ifndef Atmosphere_h
#define Atmosphere_h

// Incluso tutti gli archivi aggiuntivi necessari
#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Atmosphere {
 public:

// Costrutttori
  Atmosphere(); // Predefinito}
  Atmosphere(const string& name, double A, double C_d, double F107, double A_p); // Predefinito
  Atmosphere(const Atmosphere& atm); // Copia

// Distruttore
  ~Atmosphere();

// Metodi di accesso - Getter Methods
  double A() const;
  double C_d() const;
  double F107() const;
  double A_p() const;

// Metodi di aggiornamento - Setter Methods
  void setA(double A);
  void setC_d(double C_d);
  void setF107(double F107);
  void setA_p(double A_p);

// Memeber functions
  double T(); // Temperatura
  double mu(double h); // molecular mass of the air
  double rho(double h);// density of the air
  // Drag force: dal momento che e' parallelo alla velocita', lo tratto come uno scalare
  Vector3D D(Vector3D v, double h);

// Metodi accessori - Utility Methods
  void print() const;

 private:
  string name_;
  double A_;
  double C_d_;
  double F107_;
  double A_p_;

};
#endif
