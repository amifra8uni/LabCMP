/* app.cpp
   programma esame 27 gennaio 2021
   Francesco Amicucci 1795152 */

// Includo gli archivi di intestazione
#include <fstream> // Per l'output dei file
#include <iomanip> // Per setPrecision
#include <iostream>
#include <cmath>
#include <vector>
#include <cmath>

#include "TLorentzVector.h"
#include "TwoBodyDecay.h"

#define N_part 1e4
#define RIS 0.02

using namespace std;

int main() {

  // Start up a new random generator...
  TRandom* gen = new TRandom();
  // ...exploiting the machine clock
  gen->SetSeed(time(NULL));
  
  // Particle(double mass, double charge, double threemomentum)
  double m_B = 5.280; // GeV
  double tau_B = 1.6e-12; // s
  double tau_D = 0.4e-12; // s
  TLorentzVector B, D;
  B.SetPxPyPzE(2., 0., 0., sqrt(2.*2.+m_B*m_B));
  double m_Pi = 0.14;  // GeV
  double m_D  = 1.865; // GeV
  double m_K  = 0.494;  // GeV
  TwoBodyDecay Dec1(B, tau_B, m_Pi, m_D);
  TwoBodyDecay Dec2(D, tau_D, m_Pi, m_K);

  // Sanity check
  // ** OUTPUT**
  // storing to file integration result
  ofstream ofile;
  cout << "Salvando i dati sul file di output per il sanity check e gli impulsi di K" << endl;
  ofile.open("./sim.dat");
  ofile << "#s0" << "\t" << "#pK" << "\t" << "#xB" << "\t" << "#xD" << "\t" << "#dx" << "\t" << "#xD_mis" << endl;
  //ofile << setprecision(5) << fixed;
  
  for (int i = 0; i < N_part; i++) {

    // Primo decadimento
    Dec1.decay(gen);
    TLorentzVector p4_somma_0 = Dec1.getSon1() + Dec1.getSon2();
    double s_0 = sqrt( ( Dec1.getSon1().E() + Dec1.getSon2().E() )*( Dec1.getSon1().E() + Dec1.getSon2().E() ) - p4_somma_0.P()*p4_somma_0.P() );
    double xB = Dec1.distance_decay(gen);
    double xB_real= gen->Gaus(xB, xB*RIS);
    // Secondo decadimento
    Dec2.setMom(Dec1.getSon2());
    Dec2.decay(gen);
    Dec2.boost();
    double xD = Dec2.distance_decay(gen);
    double xD_real = gen->Gaus(xD, xD*RIS);
    ofile << s_0 << "\t"
	  << Dec2.getSon2().P() << "\t"
	  << xB  << "\t"
	  << xD + xB << "\t"
	  << xD << "\t"
	  << xD_real + xB_real << endl;
  }
  ofile.close();  // close output file before exiting
  cout << "Output file for -sanity check- successfully created\n " << endl;

  delete gen;
  
  return 0;
}
