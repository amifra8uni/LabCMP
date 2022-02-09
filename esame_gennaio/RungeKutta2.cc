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

void RungeKutta2::simulation(double tmin, double tmax, ostream& ofile) {
    
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
    
    } else  setS(foo); // Copio il valore in satellite
    
    // print to file 
    ofile << setprecision(5) << fixed;
    ofile << foo.R().getX() << "\t"
	  << foo.R().getY() << "\t"
	  << foo.R().getZ() << "\t"
	  << foo.V().getX() << "\t"
	  << foo.V().getY() << "\t"
	  << foo.V().getZ() << "\t"
	  << foo.R().magnitude() << "\t"
	  << foo.V().magnitude() << "\t" << endl;  
    // cout << "t: " << t << endl;
  }
}

