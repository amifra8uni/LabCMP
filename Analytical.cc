//Analytical.cc

#include "Analytical.h"

#include <cmath>
#include <vector>

using std::vector;

// Costruttori 
Analytical::Analytical(Velocity v0, double beta, double m, double g, double dt) : SpeedCalculator(v0, beta, m, g) {
  dt_=dt;
}

vector<Velocity> Analytical::velocity(double tmin, double tmax) const {
  vector<Velocity> v;

  double newvx = 0.;
  double newvy = 0.;

  for (double t=tmin; t<tmax; t+=dt_) {
		
    newvx = v0().Vx()*exp(-beta()*t/m());
    newvy = v0().Vy()*exp(-beta()*t/m()) - m()*g()/beta() * (1 - exp(-beta()*t/m()));
		
    v.push_back(Velocity(newvx,newvy));
  }

  return v;
}
