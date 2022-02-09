// RungeKutta2.h

#ifndef RungeKutta2_h
#define RungeKutta2_h

#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "FlySatellite.h"
#include "Vector3D.h"

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class RungeKutta2 : public FlySatellite {
 public:
  RungeKutta2(Planet p, Satellite s, Atmosphere atm, double dt);
  virtual ~RungeKutta2() {
    cout << "E' stato chiamato il distruttore di RungeKutta2" << endl;
  };
  void simulation(double tmin, double tmax, ostream& ofile); 

private:
  double dt_;
};
#endif
