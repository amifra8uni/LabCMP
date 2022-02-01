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
    
  for (double t=tmin; t<tmax; t+=dt_) {

    Satellite foo = S();

    if (foo.R().magnitude() > P().R()) {
    Vector3D K1v = dvdt(foo.V());
    
    // Mi serviva per vedere se i valori di v erano nan
    // cout << "La dvdt di Vy è " << K1v.getX() << " m/s a t = " << t <<endl; 
    K1v = K1v.operator*(dt_);
    Vector3D newv = foo.V().operator+(K1v.operator*(dt_*0.5));
    Vector3D K2v = dvdt(foo.V() + newv);

    // Per la posizione K1 = K2
    Vector3D K2x = drdt().operator*(dt_);

    // Aggiorno il passo di s nella variabile di appoggio
    foo.setV(foo.V() + K2v);
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
    
  }

  return AllSat;
}

