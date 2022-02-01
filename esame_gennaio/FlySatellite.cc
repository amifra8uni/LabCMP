// FlySatellite.cc

#include "FlySatellite.h"

// Costruttore
FlySatellite::FlySatellite(Planet p, Satellite s, Atmosphere atm) {
  p_ = p;
  s_ = s;
  atm_ = atm;
}

// Distruttore
FlySatellite::~FlySatellite() {
  cout << "\nE' stato chiamato il distruttore di FlySatellite" << endl;
}
// Setters - Metodi di aggiornamento
void FlySatellite::setP(Planet p) {p_ = p;}
void FlySatellite::setS(Satellite s) {s_ = s;}
void FlySatellite::setAtm(Atmosphere atm) {atm_= atm;}
  
// Getters - Metodi di accesso
Planet FlySatellite::P() const { return p_; }
Satellite FlySatellite::S() const {return s_;}
Atmosphere FlySatellite::Atm() const {return atm_;}

Vector3D FlySatellite::dvdt(Vector3D v) const {
  Vector3D foo = s_.R().operator*( -p_.G()*s_.M()*p_.M()/( s_.R().magnitude()*s_.R().magnitude()*s_.R().magnitude() ) );
  double h = s_.R().magnitude()-p_.R();
  foo = foo.operator+( atm_.D(v, h) );
  foo = foo.operator/(s_.M());
  return foo;
}

Vector3D FlySatellite::drdt() const {
  return s_.V();
}
