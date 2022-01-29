//RungeKutta.cc

#include "RungeKutta.h"

#include <cmath>
#include <vector>

using std::vector;

RungeKutta::RungeKutta(Velocity v0, double beta, double m, double g, double h) : SpeedCalculator(v0, beta, m, g) {
  h_=h;
}

vector<Velocity> RungeKutta::velocity(double tmin, double tmax) const {
  vector<Velocity> v;

  double newvx = v0().Vx();
  double newvy = v0().Vy();
	
  v.push_back(Velocity(newvx,newvy));

  double K1x = 0.;
  double K2x = 0.;
  double K1y = 0.;
  double K2y = 0.;

  for (double t=tmin; t<tmax; t+=h_) {
		
    K1x = h_ * newvx * (-beta()/m());
    K2x = h_ * (newvx + K1x*h_/2) * (-beta()/m());
    newvx += K2x;

    K1y = h_ * ( -g() - beta()/m()*newvy );
    K2y = h_ * ( -g() - beta()/m()*(newvy + K1y*h_/2) );
    newvy += K2y;

    v.push_back(Velocity(newvx,newvy));
  }

  return v;
}
