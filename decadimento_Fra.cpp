/*Decadimento_Fra.cpp
  Simulazione del decadimento di una particella in due particelle di massa minore*/

//Includo l'archivio di intestazione standard e quelli aggiuntivi
#include <iostream>

//Archivio di intestazione di ROOT: numeri casuali, grafici, salvataggio
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"

using namespace std;

// For the time being we will not use command line variables
int main() {

  /*Con un generatore di numeri casuali, vogliamo
    1) Generale il VALORE VERO dell'osservabile in un determinato intervallo e poi
    2) Tener contro della risuluzione del rivelatore per generale il VALORE MISURATO da quest'ultimo */
  // With a random generator, we want to
  // 1) generate the TRUE VALUE of the observable in a given range and then
  // 2) take into account the detector resolution to generate the
  //    VALUE MEASURED by the detector

  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

 // Create the B meson 4-momentum in the LAB frame
  TLorentzVector p4_B_lab;
  double M_B     = 5.279; // GeV
  double p_B_lab = 0.300; // GeV
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  p4_B_lab.SetPxPyPzE(p_B_lab, 0, 0, sqrt(p_B_lab*p_B_lab+M_B*M_B));

  // Creando il quadrimpulso del pione e del kaone nel sistem c.d.m. - Create the pion 4-momentum in the B rest frame
  double m_pi = 0.140; // GeV
  double m_K  = 0.500; // Gev
  double p_pi_cdm = sqrt( M_B*M_B*M_B*M_B + m_pi*m_pi*m_pi*m_pi + m_K*m_K*m_K*m_K - 2*M_B*M_B*m_pi*m_pi -2*M_B*M_B*m_K*m_K ) / (2*M_B); // GeV

  /* Genero 10^4 direzioni casuali
     As a reminder:
     * Hadron colliders measure physical momenta in terms of momentum transverse
       to the beam axis (z-axis); the TRANSVERSE MOMENTUM is denoted by p_T
     * p_x = p_T * cos(phi) 
       p_y = p_T * sin(phi) 
       p_z = m_T * sinh(eta) 
       E = m_T * cosh(eta) 
       where m_T = sqrt(p_T^2 + m^2) is the TRANSVERSE MASS
     * eta is the PSEUDORAPIDITY: eta = -ln[tan(theta/2)]; differences in eta
       are Lorentz invariants under boosts along the longitudinal axis
  */
  vector <TLorentzVector> p4_pi_cdm;
  vector <TLorentzVector> p4_K_cdm;
  for(int i = 0; i < 10000; i++) {
  // Genero un vettore uniformemente distribuito sulla superficie di una sfera unitaria
  double x,y,z;
  gen->Sphere(x, y, z, 1);
   p4_pi_cdm.push_back( TLorentzVector() );
   p4_K_cdm.push_back(  TLorentzVector() );
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  // CdM
  p4_pi_cdm[i].SetPxPyPzE( p_pi_cdm*x,  p_pi_cdm*y,  p_pi_cdm*z, sqrt(m_pi*m_pi+p_pi_cdm*p_pi_cdm));
  p4_K_cdm[i].SetPxPyPzE( -p_pi_cdm*x, -p_pi_cdm*y, -p_pi_cdm*z, sqrt(m_pi*m_pi+p_pi_cdm*p_pi_cdm));
  // Trasformazion (boost) nel sistema di laboratorio
  p4_pi_cdm[i].Boost(p4_B_lab.BoostVector());
 }

  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Exit
  return 0;
}
