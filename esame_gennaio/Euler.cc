// Euler.cc

#include "Euler.h"

Euler::Euler(Planet p, Satellite s, Atmosphere atm, double dt) : FlySatellite(p, s, atm) {
  dt_=dt;
  cout << "\nQuesti sono i paramatri passati a Euler\n";
  p.print();
  s.print();
  atm.print();
    cout  << "dt = " << dt << " s" << endl;
}

vector<Satellite> Euler::simulation(double tmin, double tmax) {

  vector<Satellite> AllSat;
  AllSat.push_back(S());
    
  for (double t=tmin; t<=tmax; t+=dt_) {

    Satellite foo = S();

    if (foo.R().magnitude() > P().R()) {

      // Velocita'
      Vector3D fvel = dvdt(foo.V()).operator*(dt_);
      foo.setV(foo.V()+fvel);
      // Copio il valore in satellite
      setS(foo);

      // Mi serviva per vedere se i valori di v erano nan
      //cout <<"Vx = "<< foo.V().getX() << "La dVx/dt è " << fvel.getX() << " m/s a t = " << t <<endl; 

      // Posizione
      Vector3D fpos = drdt().operator*(dt_);
      foo.setR(foo.R()+fpos);
      // Copio il valore in satellite
      setS(foo);
      AllSat.push_back(foo);
      
    } else {

      // Copio il valore in satellite
      setS(foo);
   
      AllSat.push_back(foo);
    }
    // cout << "t: " << t << endl;
  }

  return AllSat;
}
