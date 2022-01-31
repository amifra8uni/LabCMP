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
    Satellite foo;
    Vector3D Kv = dvdt(P(), Atm())*dt;
    Vector3D Kx = drdt()*dt;

    // Aggiorno il passo di s nella variabile di appoggio
    foo.setV(S().V() + Kv);
    foo.setR(S().R() + Kv);

    // Copio il valore in satellite
    setS(foo);
    AllSat.push_back(S());
  }

  return AllSat;
}

