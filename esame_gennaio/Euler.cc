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

void Euler::simulation(double tmin, double tmax, ostream& ofile) {
    
  for (double t=tmin; t<=tmax; t+=dt_) {

    Satellite foo = S();

    if (foo.R().magnitude() > P().R()) {

      // ** Velocita' **
      Vector3D fvel = dvdt(foo.V()).operator*(dt_);
      foo.setV(foo.V()+fvel);
      // Copio il valore in satellite
      setS(foo);

      // Mi serviva per vedere se i valori di v erano nan
      //cout <<"Vx = "<< foo.V().getX() << "La dVx/dt è " << fvel.getX() << " m/s a t = " << t <<endl; 

      // ** Posizione **
      Vector3D fpos = drdt().operator*(dt_);
      foo.setR(foo.R()+fpos);
      
      // Copio il valore in satellite
      setS(foo);
      
    } else {

      // Copio il valore in satellite
      setS(foo);
   
    }
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
