/* Electron_energy_loss.cpp
   programma per l'esame del 10 maggio 2021*/

// Includo l'archivio di intestazione
#include <iostream>
#include <cmath>
#include <vector>
#include <time.h>

//#include "Particle.h"
#include "Materiale.h"

//Archivio di intestazione di ROOT: grafici, salvataggio
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TString.h"
#include "TRandom3.h"
#include <vector>

using namespace std;


int main() {

  double A = 207.;
  double Z = 82.;
  double rho = 11.35;
  double I = 823.;
  double delta = 0.6;
  double X_0 = 0.56;
  double E_C = 7.4;
  double N_particles = 100;

  // Definisco il passo della mia funzione
  double dx = 100./10000.; // cm
  double res = 0.05; // Risoluzion del rivelatore
  int seed = time(0);
  srand48(seed);
  TRandom* gen = new TRandom();
  
  // Material(density, atomicMass, atomicNumber, ionisation, lung_rad, delta, e_critica);
  Materiale piombo(rho, A, Z, I, X_0, delta, E_C);
  piombo.print();

  // dEdx(particle, dx, res, gen);
  vector <double> E_i; // Mev
  E_i.push_back(10);
  E_i.push_back(1000);
  E_i.push_back(100*1000);
  for(int k = 0; k < E_i.size(); k++) {
    double x_mean = 0;
    double x_RMS = 0;
    for (int j = 0; j < N_particles; j++) {
      // Particle (mass, charge, energy [MeV])
      Particella electron(0.511, 1., E_i[k]);
      vector <double> x;
      x.push_back(0.);
      for (int i = 0; electron.K() > electron.m(); i++) {
	double perdita = piombo.dE(electron, dx, res, gen);
	electron.setE(electron.E()-perdita);
	x.push_back(x[i] + dx);
      }
      x_mean += x[x.size()-1];
      x_RMS += x[x.size()-1]*x[x.size()-1];
      //cout << "L'elettrone si è fermato dopo x_max = " << x[x.size()-1] << " cm" << endl;
    }
    x_mean /= N_particles;
    x_RMS = sqrt(x_RMS/N_particles);
    cout << "L'elettrone con energia iniziale E_i = " << E_i[k] << " MeV si è fermato in media dopo x_max = " << x_mean << " cm, con RMS = " << x_RMS << " cm" << endl;
    }
  delete gen;
  return 0;
}
