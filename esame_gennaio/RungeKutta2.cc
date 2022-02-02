// RungeKutta2.cc

#include "RungeKutta2.h"

RungeKutta2::RungeKutta2(Planet p, Satellite s, Atmosphere atm, double dt) : FlySatellite(p, s, atm) {
  dt_=dt;
  cout << "\nQuesti sono i paramatri passati a RungeKutta2\n";
  p.print();
  s.print();
  atm.print();
    cout  << "dt = " << dt << " s" << endl;
}

vector<Satellite> RungeKutta2::simulation(double tmin, double tmax) {

  vector<Satellite> AllSat;
  AllSat.push_back(S());
    
  for (double t=tmin; t<=tmax; t+=dt_) {

    Satellite foo = S();

    if (foo.R().magnitude() > P().R()) {
    Vector3D K1v = dvdt(foo.V());
    K1v = K1v.operator*(dt_);
    
    // Mi serviva per vedere se i valori di v erano nan
    //cout <<"Vx = "<< foo.V().getX() << "La dVx/dt è " << K1v.getX() << " m/s a t = " << t <<endl; 
    //cout << "dv/dt * dt = " << K1v.getX() << endl;

    Vector3D newv = foo.V().operator+(K1v.operator*(dt_*0.5));
    Vector3D K2v = dvdt(newv).operator*(dt_);
    foo.setV(foo.V() + K2v);
    setS(foo); // Se non faccio questo la posizione del satellite verrà aggiornata con la velocita' vecchia
    
    // Per la posizione K1 = K2
    Vector3D K2x = drdt().operator*(dt_);
    foo.setR(foo.R() + K2x);

    // Copio il valore in satellite
    setS(foo);
    
    AllSat.push_back(foo);
    } else {
      
      Vector3D Nullv = Vector3D::Cartesiane(0.,0.,0.);
      foo.setV(Nullv);

      // Copio il valore in satellite
      setS(foo);
   
      AllSat.push_back(foo);
    }
    // cout << "t: " << t << endl;
  }

  return AllSat;
}

