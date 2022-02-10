/* Electron_energy_loss.cpp
   programma per l'esame del 10 maggio 2021*/

// Includo l'archivio di intestazione
#include <fstream> // Per il file di output
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>

//#include "Particle.h"
#include "Material.h"
#include "Particle.h"

//Archivio di intestazione di ROOT: grafici, salvataggio
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom3.h"

using namespace std;


int main() {

  double A = 207.;
  double Z = 82.;
  double rho = 11.35;
  double I = 823.;
  double delta = 0.6;
  double X_0 = 0.56;
  double E_C = 7.4;
  double N_particles = 1e4;

  // Definisco il passo della mia funzione
  double dx = 0.01; // cm 
  double res = 0.05; // Risoluzion del rivelatore
  TRandom* gen = new TRandom();
  
  // Material(density, atomicMass, atomicNumber, ionisation, lung_rad, delta, e_critica);
  Material piombo(rho, A, Z, I, X_0, delta, E_C);
  piombo.print();

  // dEdx(particle, dx, res, gen);
  double E_i = 1e3; // MeV

  double x_mean = 0;
  double x_RMS = 0;

  // ** FILE DI OUTPUT **
  // storing to file integration result
  ofstream ofile;
  cout << "Salvando i dati sul file di output " << endl;
  ofile.open("./xmax-1gev.dat");
  ofile << "#xmax" <<  endl;

  // Simulazione per N elettroni
  for (int j = 0; j < N_particles; j++) {
    // Particle (mass, charge, energy [MeV])
    Particle electron(0.511, 1., E_i);
    vector <double> x;
    x.push_back(0.);

    // Simulazione per un elettrone finche' non perde tutta l'energia
    for (int i = 0; electron.K() > electron.m(); i++) {
      double perdita = piombo.dE(electron, dx, res, gen, E_i, x[i]+dx);
      electron.setE(electron.E()-perdita);
      x.push_back(x[i] + dx);
    }

    // Stampo sul file di output
    ofile << x[x.size()-1] << endl;;
    x_mean += x[x.size()-1];
    x_RMS += x[x.size()-1]*x[x.size()-1];
  }
  x_mean /= N_particles;
  x_RMS = sqrt(x_RMS/N_particles);

  ofile.close();  // close output file before exiting
  cout << "Output file successfully created\n " << endl;

  cout << "L'elettrone con energia iniziale E_i = " << E_i << " MeV si e' fermato in media dopo x_max = " << x_mean << " cm, con RMS = " << x_RMS << " cm" << endl;
 
  delete gen;
  return 0;
}
