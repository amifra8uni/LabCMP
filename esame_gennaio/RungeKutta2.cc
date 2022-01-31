// RungeKutta2.cc

#include "RungeKutta2.h"

RungeKutta2::RungeKutta2(Planet p, Satellite s, Atmosphere atm, double dt) : FlySatellite(p, s, atm) {
  dt_=dt;
  cout << "RungeKutta2("<< p.print()
       << ", " << s.print()
       << ", " << atm.print()
       << ", " << dt << endl;
}

vector<Satellite> RungeKutta2::simulation(double tmin, double tmax) const {

  vector<Satellite> AllSat;
  sat.push_back(S());

  for (double t=tmin; t<tmax; t+=dt_) {
    satellite foo;

    Vector3D K1v = dvdt(s.V())*dt_;
    Vector3D newv = s.V().operator+(K1v.operator*(dt_*0.5));
    Vector3D K2v = dvdt(s.V() + newv);

    Vector3D K2x = drdt();

    // Aggiorno il passo di s nella variabile di appoggio
    foo.setV(s.V() + K2v);
    foo.setR(s.R() + K2x);

    // Copio il valore in satellite
    s.setS(foo);
    AllSat.push_back(s);
  }

  return AllSat;
}

