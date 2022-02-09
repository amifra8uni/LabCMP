/* app.cpp
   File in C++ per l'esame di gennaio 2022 di CMP
   Francesco Amicucci 1795152                    */

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
#include <cstring>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define LEN 30
#define MT 5.972e24 // kg
#define RT 6371e3   // m
#define CGU 6.67e-11  // N m^2/kg^2

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
  char metodo_integrazione[LEN];
  double dt;        // s
  int Nsteps = 0.;
  double r0;        // m
  double m_Sat;     // kg
  double A = 0;     // m^2 cross sectional area of the object 
  double F107 = 80; // Solar radio flux
  double C_d = 2;   // Drag coefficient
  double A_p = 50;  // Geomagnetic index

  // loop over file until end-of-file
  while(!infile.eof()) {
    // get current line
    getline(infile, line);
    if( line == "\n" || line == "" || line == "# metodo_integrazione, dt, Nsteps, r0, m_Sat, A, F107, C_d, A_p") continue;

    // parse line with the provided format and put data in variables
    // NB: USING POINTERS TO VARIABLES
    // format:  %s string    %f  float   %lf  double
    sscanf(line.c_str(),"%s %lf %d %lf %lf %lf %lf %lf %lf", metodo_integrazione, &dt, &Nsteps, &r0, &m_Sat, &A, &F107, &C_d, &A_p);

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
	 <<" \nGeomatrical index: " << A_p << endl;
  } // !eof
  
  // Definisco i miei oggetti
  Planet Earth("Earth", RT, MT, CGU);   // Planet(name, radius, mass, grav const)

  // Controllo che l'altezza del satellite inserita non sia negativa
  if(r0 < 0) {
    cerr << "\n***Non puoi mettere il tuo satellite sotto la superficie!\nRiprova con un r0 (il IV paramentro) positivo***\n" << endl;
    exit(EXIT_FAILURE);
  }

  // Atmosphere(double A, double C_d, double F107, double A_p)
  Atmosphere aria("Aria", A, C_d, F107, A_p);
  aria.print();

  Vector3D r = Vector3D::Cartesiane(r0 + RT, 0 ,0);
  Vector3D v = Vector3D::Cartesiane(0, sqrt(Earth.G()*Earth.M()/(r0+Earth.R())), 0);
  // Vector3D v = Vector3D::Cartesiane(0, 0, 0); // Prova oggetto in caduta libera
  Satellite sat("Satellite1", r, v, m_Sat);
  sat.print();

  // Scelgo il metodo di integrazione
  // RK2 (Planet, Satellite, Atmosphere, double dt)
  FlySatellite* met = 0;
  if (!strcmp(metodo_integrazione, "RungeKutta2")) met = new RungeKutta2(Earth, sat, aria, dt); 
  else if (!strcmp(metodo_integrazione, "Euler"))  met = new Euler(Earth, sat, aria, dt);
  else {
    cerr << "\n*** Il metodo di integrazione selezionato" << metodo_integrazione << " non e' corretto ***\nScegliere tra: RungeKutta2 e Euler\n" << endl;
    exit(EXIT_FAILURE);
  }

  // Definisco il passo di integrazione e gli estremi
  double tmin = 0;
  double tmax = Nsteps*dt;
  vector <Satellite> simulazione = met->simulation(tmin, tmax);

  // ** OUTPUT**
   // storing to file RK result
  ofstream ofile;
  //string ofnam("./sim2_dt_1_N_20k.dat");
  cout << "Salvando i dati sul file di output " << endl;
  ofile.open("./simRK_dt_1_N_20k_h600km.dat");

  // print to file 
  ofile << "#x"  << "\t" << "#y" << "\t" << "#z" << "\t" << "#vx" << "\t" << "#vy" << "\t" << "#vz" << "\t" << "#r" << "\t" << "#v" << endl;
  for(vector<Satellite>::const_iterator it = simulazione.begin(); it != simulazione.end(); ++it) {
    ofile << setprecision(5) << fixed;
    ofile << it->R().getX() << "\t"
	  << it->R().getY() << "\t"
	  << it->R().getZ() << "\t"
	  << it->V().getX() << "\t"
	  << it->V().getY() << "\t"
	  << it->V().getZ() << "\t"
	  << it->R().magnitude() << "\t"
	  << it->V().magnitude() << "\t" << endl;
  }

  infile.close(); // close input file before exiting
  ofile.close();  // close output file before exiting
  cout << "Output file successfully created\n " << endl;

  delete met;
  return 0;
}
