/* app.cpp
   File in C++ per l'esame di gennaio 2022 di CMP*/

// Includo gli archivi di intestazione
#include "RungeKutta2.h"
#include "Planet.h"
#include "Satellite.h"
#include "Atmosphere.h"
#include "Vector3D.h"
#include "FlySatellite.h"
#include "Euler.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


int main() {

  // ** INPUT **
  // Nome del file
  const char filename[30] = "./params.ini";

  // Create object for input file
  ifstream infile(filename); // Input file object

  // String to hold each line
  string line;

  // Make sure input file is open otherwise exit
  if(!infile.is_open()) {
    cerr << "Non risco ad aprire il file di input " << filename << endl;
    exit(EXIT_FAILURE);
  }

  // Variables to read in from file
  int metodo_integrazione;
  double dt;        // s
  int Nsteps = 0.;
  double r0;        // m
  double m_Sat;     // kg
  double A = 0;     // cross sectional area of the object
  double F107 = 80; // Solar radio flux
  double C_d = 2;   // Drag coefficient
  double A_p = 50;  // Geomagnetic index

  // loop over file until end-of-file
  while(!infile.eof()) {
    // get current line
    getline(infile, line);
    if( line == "\n" || line == "" ) continue;

    // parse line with the provided format and put data in variables
    // NB: USING POINTERS TO VARIABLES
    // format:  %s string    %f  float   %lf  double
    sscanf(line.c_str(),"%d %lf %d %lf %lf %lf %lf %lf %lf", &metodo_integrazione, &dt, &Nsteps, &r0, &m_Sat, &A, &F107, &C_d, &A_p);

    // print out for debug purposes
    cout << "I parametri presi in input sono (presi tutti su una linea)\n"
	 << "Metodo di integrazione: " << metodo_integrazione
	 << "\tdt: " << dt
	 << "\tN passi: " << Nsteps
	 << "\tAltezza satllite: " << r0
      	 << "\nMassa del satellite: " << m_Sat
	 << "\tCross sec. area: " << A
	 << "\tSolar radio flux: " << F107
	 << "\tDrag coefficient: " << C_d
	 <<" \nGeomatrical indez: " << A_p << endl;
  } // !eof
  
  // Definisco i miei oggetti
  double MT = 5.972*pow(10,24);// kg
  double RT = 6371.*1000.;     // m
  double G = 6.67*pow(10,-11); // N m^2/kg^2
  Planet Earth("Earth", RT, MT, G);   // Planet(name, radius, mass, grav const)

  // Controllo che l'altezza del satellite inserita non sia negativa
  if(r0 < 0) {
    cerr << "\n***Non puoi mettere il tuo satellite sotto la superficie!\nRiprova con un r0 (il IV paramentro) positivo***\n" << endl;
    exit(EXIT_FAILURE);
  }

  // Atmosphere(double A, double C_d, double F107, double A_p)
  Atmosphere aria("Aria", A, C_d, F107, A_p);
  aria.print();

  Vector3D r = Vector3D::Cartesiane(r0 + RT, 0 ,0);
  //   Vector3D v = Vector3D::Cartesiane(0, sqrt(Earth.G()*Earth.M()/(r0+Earth.R())), 0);
  Vector3D v = Vector3D::Cartesiane(0, 0, 0); // Prova oggetto in caduta libera
  Satellite sat("Satellite1", r, v, m_Sat);
  sat.print();

  // Scelgo il metodo di integrazione
  // RK2 (Planet, Satellite, Atmosphere, double dt)
  FlySatellite* met = 0;
  if(metodo_integrazione == 0) met = new RungeKutta2(Earth, sat, aria, dt);
  else if (metodo_integrazione == 1) met = new Euler(Earth, sat, aria, dt);
  else {
    cerr << "\n***Il metodo di integrazione selezionato" << metodo_integrazione << " non è corretto\nScegliere tra: 0 (RungeKutta2) e 1 (Eulero)***\n" << endl;
    exit(EXIT_FAILURE);
  }

  // Definisco il passo di integrazione e gli estremi
  double tmin = 0;
  double tmax = Nsteps*dt;
  vector <Satellite> simulazione = met->simulation(tmin, tmax);

  // ** OUTPUT**
   // storing to file RK result
  ofstream ofile;
  string ofname("./sim1_Eu_100.dat");
  cout << "Salvando i dati su " << ofname << endl;
  ofile.open( ofname );

  // print to file 
  ofile << "#x"  << "\t" << "#y" << "\t" << "#z" << "\t" << "#vx" << "\t" << "#vy" << "\t" << "#vz" << endl;
  for(vector<Satellite>::const_iterator it = simulazione.begin(); it != simulazione.end(); ++it) {
    ofile << setprecision(5) << fixed;
    ofile << it->R().getX() << "\t"
	  << it->R().getY() << "\t"
	  << it->R().getZ() << "\t"
	  << it->V().getX() << "\t"
	  << it->V().getY() << "\t"
	  << it->V().getZ() << "\t" << endl;
  }

  infile.close(); // close input file before exiting
  ofile.close();  // close output file before exiting
  cout << ofname << " output file successfully created\n " << endl;

  delete met;
  return 0;
}
