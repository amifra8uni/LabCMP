// app.cpp

// Includo gli archivi di intestazione
#include "Velocity.h"
#include "Analytical.h"
#include "RungeKutta.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

#define V0X  15   // m/s
#define V0Y  15   // m/s
#define M    25   // kg
#define BETA 0.15 // Ns/m
#define G    9.80 // m/S

using namespace std;

int main() {

  // Definisco il passo della funzione
  double dt = 0.001; // s
  double h = 0.001;

  // Definisco un vettore velocita'
  Velocity v0(V0X, V0Y);
  v0.print();

  // Definisco le mie due classi per la soluzione dell'eq. diff
  Analytical analytical(v0, BETA, M, G, dt);
  RungeKutta rungekutta(v0, BETA, M, G, h);

  // Definisco gli estremi per il plot 
  double tmin = 0.;
  double tmax = 1.5;

  // In questo vettore salvo i valori delle velocità (un vettore di due) per ogni t
  vector<Velocity> allvAn;
  vector<Velocity> allvRK;
  allvAn = analytical.velocity(tmin, tmax);
  allvRK = rungekutta.velocity(tmin, tmax);
	
  double t = 0;

  // storing to file Analytical result
  ofstream ofile;
  string ofname("./dataAn.txt");
  cout << "storing data in " << ofname << endl;
  ofile.open( ofname );

  ofile << "#vx" << "\t" << "#vy" << "\t" << "#t" << endl;
  for(vector<Velocity>::const_iterator it=allvAn.begin(); it != allvAn.end(); ++it) {
    ofile << setprecision(5) << fixed;
    ofile << it->Vx() << "\t" << it->Vy() << "\t" << t << endl;
    t+=h;
  }

  ofile.close();
  cout << ofname << " output file successfully created" << endl;

  t = 0;

  // storing to file RK result
  ofstream ofile2;
  string ofname2("./dataRK.txt");
  cout << "storing data in " << ofname2 << endl;
  ofile2.open( ofname2 );

  ofile2 << "#vx" << "\t" << "#vy" << "\t" << "#t" << endl;
  for(vector<Velocity>::const_iterator it=allvRK.begin(); it != allvRK.end(); ++it) {
    ofile2 << setprecision(5) << fixed;
    ofile2 << it->Vx() << "\t" << it->Vy() << "\t" << t << endl;
    t+=h;
  }

  ofile2.close();
  cout << ofname2 << " output file successfully created" << endl;

  return 0;
}
