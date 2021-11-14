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
#include "THStack.h"
#include "Vector3D.h"

using namespace std;

// For the time being we will not use command line variables
int main() {

    // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
    std::cout << "problems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

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
  TLorentzVector p4_B, p4_pi, p4_K;
  double M_B     = 5.279; // GeV
  double p_B = 0.300; // GeV
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B + M_B*M_B));

  // Creando il quadrimpulso del pione e del kaone nel sistem c.d.m. - Create the pion 4-momentum in the B rest frame
  double m_pi  = 0.140; // GeV
  double m_K   = 0.500; // Gev
  double p = sqrt( M_B*M_B*M_B*M_B + m_pi*m_pi*m_pi*m_pi + m_K*m_K*m_K*m_K - 2*M_B*M_B*m_pi*m_pi - 2*M_B*M_B*m_K*m_K ) / (2*M_B); // GeV

  // Istogramma della massa invariante (name, title, number of bins, range)
  int    nbins = 200;
  double resol = 0.1;
  double xlo   = M_B*(1-3*resol);
  double xhi   = M_B*(1+3*resol);
  double binwidth = (xhi-xlo) / nbins;
  vector<TH1F> histo;
  vector<short int> colore = {kBlue, kRed, kGreen, kYellow};
  THStack hs("hs", "Sovrimpressione s teorico e misurato");
  THStack hsris("hsris", "Sovrimpressione s misurato per diverse risoluzioni");
  TH1F hs0("hs", "Distribuzione della massa invariante", nbins, xlo, xhi);
  TH1F hangle("hangle", "Distribuzione dell'angolo di apertura tra K e pi", nbins, 0, 180);
  // The 'd' is for detector
  /*TH1F hds1( "hds1"  , "Distribuzione della massa invariante misurata", nbins, xlo , xhi);
  TH1F hds3( "hds3"  , "Distribuzione della massa invariante misurata", nbins, xlo , xhi);
  TH1F hds5( "hds5"  , "Distribuzione della massa invariante misurata", nbins, xlo , xhi);
  TH1F hds10("hds10" , "Distribuzione della massa invariante misurata", nbins, xlo , xhi);*/
  histo.push_back(TH1F( "hds1" , "Distribuzione della massa invariante misurata", nbins, xlo , xhi) );
  histo.push_back(TH1F( "hds3" , "Distribuzione della massa invariante misurata", nbins, xlo , xhi) );
  histo.push_back(TH1F( "hds5" , "Distribuzione della massa invariante misurata", nbins, xlo , xhi) );
  histo.push_back(TH1F("hds10" , "Distribuzione della massa invariante misurata", nbins, xlo , xhi) );
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
       are Lorentz invariants under boosts along the longitudinal axis */ 
  for(int i = 0; i < 10000; i++) {
    // Genero un vettore uniformemente distribuito sulla superficie di una sfera unitaria
    double x, y, z, s_0, p_K_0, p_pi_0, p_K_meas, p_pi_meas;
    double ris[4] = {0.01, 0.03, 0.05, 0.1};
    gen->Sphere(x, y, z, 1);
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    // CdM
    p4_pi.SetPxPyPzE( p*x,  p*y,  p*z, sqrt(m_pi*m_pi + p*p));
    p4_K.SetPxPyPzE( -p*x, -p*y, -p*z, sqrt(m_K*m_K   + p*p));

    // Trasformazion (boost) nel sistema di laboratorio
    p4_pi.Boost(p4_B.BoostVector());
    p4_K.Boost( p4_B.BoostVector());

    //Calcolo massa invariante
    TLorentzVector p4_somma_0 = p4_K + p4_pi;
    s_0 = sqrt( ( p4_K.E() + p4_pi.E() )*( p4_K.E() + p4_pi.E() ) - p4_somma_0.P()*p4_somma_0.P() );
    hs0.Fill(s_0);
    hangle.Fill(p4_K.Angle(p4_pi.Vect())*180/M_PI);

    p_K_0  = p4_K.P();
    p_pi_0 = p4_pi.P();
    // Generate MEASURED value based on the true value and resolution
    for(int j = 0; j < histo.size(); j++) {
      p_pi_meas = gen->Gaus(p_pi_0, p_pi_0*ris[j]);
      p_K_meas  = gen->Gaus(p_K_0,  p_K_0*ris[j] );
      p4_pi.SetPxPyPzE( p_pi_meas*sin(p4_pi.Theta())*cos(p4_pi.Phi()),  p_pi_meas*sin(p4_pi.Theta())*sin(p4_pi.Phi()),  p_pi_meas*cos(p4_pi.Theta()), sqrt(m_pi*m_pi + p_pi_meas*p_pi_meas));
      p4_K.SetPxPyPzE ( p_K_meas*sin(p4_K.Theta()  )*cos( p4_K.Phi()) , p_K_meas*sin( p4_K.Theta() )*sin( p4_K.Phi()) , p_K_meas*cos( p4_K.Theta()) , sqrt(m_K*m_K   + p_K_meas*p_K_meas  ));
      //Calcolo massa invariante misurata
      TLorentzVector p4_somma_mis = p4_K + p4_pi;
      double s_mis = sqrt( ( p4_K.E() + p4_pi.E() )*( p4_K.E() + p4_pi.E() ) - p4_somma_mis.P()*p4_somma_mis.P() );
      histo[j].Fill(s_mis);
    }
  }

  // After generating the data, we take care of plotting the results:
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  // * start from TRUE values and customize some histogram properties
  hs0.GetXaxis()->SetTitle( "Distribuzione di s [GeV]");
  histo[1].GetXaxis()->SetTitle("Distribuzione di s misurata [GeV]");
  hangle.GetXaxis()->SetTitle("Distribuzione angolare [�]");
  // * plot e store to file in 1 formats
  hs0.Draw();
  canv.SaveAs("./true-mass.pdf");
  histo[0].Draw();
  canv.SaveAs("./measured-mass-1per.pdf");
  histo[1].Draw();
  canv.SaveAs("./measured-mass.pdf");
  hangle.Draw();
  canv.SaveAs("./opening-angle.pdf");

  hs0.SetFillColor(kRed);
  hs.Add(&hs0);
  histo[1].SetFillColor(kBlue);
  hs.Add(&histo[1]);
  hs.Draw();
  canv.SaveAs("./invariant-mass.pdf");

  for(int k = 0; k < colore.size(); k++) {
    histo[k].SetFillColor(colore[k]);
    hsris.Add(&histo[k]);
  }
  hsris.Draw();
  canv.SaveAs("./invariant-masses.pdf");
  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Salve entrambi gli istrogrammi in un archivio
  hs0.Write();
  histo[1].Write();
  hangle.Write();
  
  // Critical to close the file!
  rfile.Close();
  
  // Exit
  return 0;
}
