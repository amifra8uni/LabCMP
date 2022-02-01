// FlySatellite.h

#ifndef FlySatellite_h
#define FlySatellite_h

#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "Vector3D.h"

#include <vector>
#include <iostream>

using namespace std;

class FlySatellite {
public:

  // Costruttore 
  FlySatellite(Planet p, Satellite s, Atmosphere atm);

  //Distruttore
  ~FlySatellite();
  
  // Setters - Metodi di aggiornamento
  void setP(Planet p);
  void setS(Satellite s);
  void setAtm(Atmosphere atm);
  
  // Getters - Metodi di accesso
  Planet P() const;
  Satellite S() const;
  Atmosphere Atm() const;

  virtual vector <Satellite> simulation(double tmin, double tmax) = 0;

  Vector3D dvdt(Vector3D v) const;
  Vector3D drdt() const;
  
private:
  Planet p_;
  Satellite s_;
  Atmosphere atm_;
};
#endif
