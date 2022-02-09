// Euler.h

#ifndef Euler_h
#define Euler_h

#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "FlySatellite.h"
#include "Vector3D.h"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Euler : public FlySatellite {
 public:
  Euler(Planet p, Satellite s, Atmosphere atm, double dt);
  virtual ~Euler() {
    cout << "E' stato chiamato il distruttore della classe Euler" << endl;
  };
  virtual void simulation(double tmin, double tmax,  ostream& ofile); 

private:
  double dt_;
};
#endif
