/*Decadimento_Fra.cpp
  Simulazione del decadimento di una particella in due particelle di massa minore*/

//Includo l'archivio di intestazione standard e quelli aggiuntivi
#include <iostream>
#include <time.h>

//Archivio di intestazione di ROOT: numeri casuali, grafici, salvataggio
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "Vector3D.h"
#include "TTree.h"

#define NDAU 2

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
  
  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(time(NULL));

 // Create the B meson 4-momentum in the LAB frame
  TLorentzVector p4_B, p4_pi, p4_K;
  double M_B = 5.279; // GeV
  double p_B = 0.300; // GeV
  // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
  p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B + M_B*M_B));

  // Creando il quadrimpulso del pione e del kaone nel sistem c.d.m. - Create the pion 4-momentum in the B rest frame
  double m_pi  = 0.140; // GeV
  double m_K   = 0.500; // Gev
  double p_cdm = sqrt( M_B*M_B*M_B*M_B + m_pi*m_pi*m_pi*m_pi + m_K*m_K*m_K*m_K - 2*M_B*M_B*m_pi*m_pi - 2*M_B*M_B*m_K*m_K ) / (2*M_B); // GeV
  double nmass[NDAU] = {m_pi, m_K};
  // Istogramma della massa invariante (name, title, number of bins, range)
  int    nbins = 200;
  double resol = 0.1;
  double xlo   = M_B*(1-3*resol);
  double xhi   = M_B*(1+3*resol);
  double binwidth = (xhi-xlo) / nbins;
  vector<TH1F> histo;
  vector<short int> colore = {kBlue, kRed, kGreen, kYellow};
  TH1F hs0("hs", "Distribuzione della massa invariante", nbins, xlo, xhi);
  TH1F hangle("hangle", "Distribuzione dell'angolo di apertura tra K e pi", nbins, 0, 180);
    
  histo.push_back(TH1F( "hds1" , "Distribuzione della massa invariante misurata con risoluzione 1%" , nbins, xlo , xhi) );
  histo.push_back(TH1F( "hds3" , "Distribuzione della massa invariante misurata con risoluzione 3%" , nbins, xlo , xhi) );
  histo.push_back(TH1F( "hds5" , "Distribuzione della massa invariante misurata con risoluzione 5%" , nbins, xlo , xhi) );
  histo.push_back(TH1F("hds10" , "Distribuzione della massa invariante misurata con risoluzione 10%", nbins, xlo , xhi) );
  
  // === Salva i dati in un TTree
  // Crea un nuovo oggetto TTree
  TTree* tree = new TTree("datatree", "albero contenente i nostri dai");
  // Il nome degli oggetti TTree (datatree), e non il nome della variabile
  // C++ (tree), è importante perchè ROOT salva tutti gli oggetti in un
  // TFile con il loro nome

  //Variabili che devono essere salvate nell'albero (rami): 
  double nDau = NDAU;
  double p[NDAU], theta[NDAU], phi[NDAU];

  // Fai si che le informazioni per ogni ramo dell'albero corrispondano ai nostri dati:
  // Una funzione di un ramo ha 3 argomenti:
  // * il nome del ramo
  // * un puntatore alla variabile in memoria
  // * il tipo di variabile nel ramo ("value/D" che è un double)
  tree->Branch("Impulso del mesone B",                     &p_B, "Impulso del mesone B/D");
  tree->Branch("Massa delle particelle figlie",            &nmass, "Massa delle particelle/D");
  tree->Branch("Numero particelle figlie",                 &nDau, "Numero particelle figlie/D");
  tree->Branch("Impulso delle particelle figlie",          &p, "Impulso delle particelle figlie/D");
  tree->Branch("Angolo phi rispetto alla linea di volo",   &phi, "Angolo phi rispetto alla linea di volo");
  tree->Branch("Angolo theta rispetto alla linea di volo", &theta, "Angolo theta rispetto alla linea di volo");

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
    double x, y, z, s_0, p_K_meas, p_pi_meas;
    double ris[4] = {0.01, 0.03, 0.05, 0.1};
    gen->Sphere(x, y, z, 1);
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    // CdM
    p4_pi.SetPxPyPzE( p_cdm*x,  p_cdm*y,  p_cdm*z, sqrt(m_pi*m_pi + p_cdm*p_cdm));
    p4_K.SetPxPyPzE( -p_cdm*x, -p_cdm*y, -p_cdm*z, sqrt(m_K*m_K   + p_cdm*p_cdm));

    // Trasformazion (boost) nel sistema di laboratorio
    // Lab
    p4_pi.Boost(p4_B.BoostVector());
    p4_K.Boost( p4_B.BoostVector());
    p[0] = p4_pi.P();
    p[1] = p4_K.P();
    theta[0] = p4_pi.Theta();
    theta[1] = p4_K.Theta();
    phi[0] = p4_pi.Phi();
    phi[1] = p4_K.Phi();
    //Calcolo massa invariante
    TLorentzVector p4_somma_0 = p4_K + p4_pi;
    s_0 = sqrt( ( p4_K.E() + p4_pi.E() )*( p4_K.E() + p4_pi.E() ) - p4_somma_0.P()*p4_somma_0.P() );
    hs0.Fill(s_0);
    hangle.Fill(p4_K.Angle(p4_pi.Vect())*180/M_PI);

    double p_K_0  = p4_K.P();
    double p_pi_0 = p4_pi.P();
    
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
    tree->Fill();
  }

  // After generating the data, we take care of plotting the results:
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  
  // * start from TRUE values and customize some histogram properties
  hs0.GetXaxis()->SetTitle( "Massa invariante s [GeV]");
  histo[1].GetXaxis()->SetTitle("Massa invariante s [GeV]");
  hangle.GetXaxis()->SetTitle("Angolo di apertura [°]");
  
  // * plot e store to file in 1 formats
  hs0.SetFillColor(kBlue);
  hs0.Draw();
  canv.SaveAs("./true-mass.pdf");
  histo[1].SetFillColor(kBlue);
  histo[1].Draw();
  canv.SaveAs("./measured-mass.pdf");
  hangle.SetFillColor(kBlue);
  hangle.Draw();
  canv.SaveAs("./opening-angle.pdf");

  hs0.SetFillColor(kRed);
  hs0.Draw();
  histo[1].SetFillColor(kBlue);
  histo[1].Draw("same");
  canv.SaveAs("./invariant-mass.pdf");

  histo[1].GetXaxis()->SetTitle("Massa invariante s [GeV]");
  histo[0].SetFillColor(kBlue);
  histo[0].Draw();
  for(int k = 1; k < colore.size(); k++) {
    histo[k].SetFillColor(colore[k]);
    histo[k].Draw("same");
  }
  //hsris.Draw();
  canv.SaveAs("./invariant-masses.pdf");

  // Sovrascrivere materialmente l'alberto in un archivio sul disco
  tree->Write();

  // Stampare alcune informazioni sull'albero
  tree->Print();
  
  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Salve entrambi gli istrogrammi in un archivio
  hs0.Write();
  histo[1].Write();
  hangle.Write();

  // Critical to close the file!
  rfile.Close();
  
  // === Finito di salvare i dati in un TTree
  delete tree;

  // Exit
  return 0;
}
