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
  FlySatellite(Planet p, Satellite s, Atmosphere atm) {
    p_ = p;
    s_ = s;
    atm_ = atm;
  }

  // Setters - Metodi di aggiornamento
  virtual void setP(Planet p) {p_ = p;}
  virtual void setS(Satellite s) {s_ = s;}
  virtual void setAtm(Atmosphere atm) {atm_= atm;}
  
  // Getters - Metodi di accesso
  virtual Planet P() const { return p_; }
  virtual Satellite S() const {return s_;}
  virtual Atmosphere Atm() const {return atm_;}

  virtual vector <Satellite> simulation(double tmin, double tmax) const = 0;

  Vector3D dvdt(Vector3D v) {
    Vector3D foo = s.r_.operator*(-p_.G()*s_.M()*p_.M()/(s_.R().magnitude()*sqrt(s_.R().magnitude())));
    foo = foo.operator+(atm.D(v, r_.Y()));
    foo = foo.operator/(s_.M());
    return foo;
  }

  Vector3D drdt() {
    return s_.V();
  }

private:
  Planet p_;
  Satellite s_;
  Atmosphere atm_;
};
#endif
