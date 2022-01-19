/* app.cpp
   programma di prova */

// Includo l'archivio di intestazione
#include <iostream>
#include <cmath>
#include <vector>

//#include "Particle.h"
#include "Material.h"

//Archivio di intestazione di ROOT: grafici, salvataggio
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TString.h"

using namespace std;
#define A 28.
#define Z 14.
#define RHO 2.33
#define I 173.
#define DELTA 0

int main() {

  Particle alpha(3.7, 2., 1.);
  cout << "triimpulso alpha: " << alpha.p() << endl;
  Particle proton(0.938, 1., 1.);
  cout << "triimpulso protone: " << proton.p() << endl;
  Material silicon(RHO, A, Z, I);

  // Open TFile for output
  TString rootfname("./output_app.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
  std::cout << "problems creating root file. existing... " << std::endl;
  exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

  vector <double> xalpha, xp, dE_dx_p, dE_dx_Alpha;

  //definisco il passo della mia funzione
  double dx = 0.1; // cm
  int i = 0;
  double T_Proto, T_Alpha, E_Proto, E_Alpha;
  E_Proto = sqrt(proton.p()*proton.p() + (proton.m()*proton.m()));
  E_Alpha = sqrt(alpha.p()*alpha.p()   + (alpha.m()*alpha.m()));
  T_Proto = E_Proto - proton.m();
  T_Alpha = E_Alpha - alpha.m();

  // PROTONE
  while (T_Proto >= 0) {

    // Calcolo la perdita di energia per le due particelle
    // Salvo i dati per il grafico
    dE_dx_p.push_back( silicon.dEdx(proton, DELTA) );
    xp.push_back( i*dx );

    // Ricalcolo le energie della particella
    T_Proto -= dE_dx_p[i]*dx; // GeV
    E_Proto -= dE_dx_p[i]*dx;

    // Controllo che la particelle non abbia perso tutta la sua energia
    // Aggiorno il trimomento della particelle dopo la perdita di energia
    if( T_Proto >= 0) proton.setP(sqrt( E_Proto*E_Proto - proton.m()*proton.m() ));
    else proton.setP(0);

    i++;
  }

  int Np = xp.size();
  xp.push_back(xp[Np-1]);
  dE_dx_p.push_back(0);
  int j=0;

  // ALPHA
  while (T_Alpha >= 0) {

    // Calcolo la perdita di energia per le due particelle
    // Salvo i dati per il grafico
    dE_dx_Alpha.push_back( silicon.dEdx(alpha, DELTA) );
    cout << "triimpulso alpha: " << alpha.p() << endl;
    cout << "energia persa : " << silicon.dEdx(alpha, DELTA)*dx << endl;
    cout << "betagamma alpha: " << alpha.betagamma() << endl << endl;;
    xalpha.push_back( j*dx );

    // Ricalcolo le energie della particella
    T_Alpha -= dE_dx_Alpha[j]*dx; // GeV
    E_Alpha -= dE_dx_Alpha[j]*dx;

    // Controllo che la particelle non abbia perso tutta la sua energia
    // Aggiorno il trimomento della particelle dopo la perdita di energia
    if( T_Alpha >= 0) alpha.setP(sqrt( E_Alpha*E_Alpha - alpha.m()*alpha.m() ));
    else alpha.setP(0);

    j++;
  }

  int N_Alpha = xalpha.size();
  xalpha.push_back(xalpha[N_Alpha-1]);
  dE_dx_Alpha.push_back(0);


  // PLOTS
  TCanvas canv("canv", "canvas for plotting", 1920, 1080);
  canv.SetGrid();
  canv.SetLogx();

  TGraph* gr1 = new TGraph(xp.size(), &xp[0], &dE_dx_p[0]);
  gr1->SetTitle("Energia persa per un protone di 1 GeV nel silicio; Profondità x [cm];Energia persa [Mev/cm]");
  gr1->SetLineColor(2);
  gr1->SetLineWidth(2);
  gr1->SetMinimum(0);
  gr1->SetMaximum(5);
  gr1->Draw();

  TGraph* gr2 = new TGraph(xalpha.size(), &xalpha[0], &dE_dx_Alpha[0]);
  gr2->SetLineColor(4);
  gr2->SetLineWidth(2);
  gr2->Draw("same");

  TLegend* leg = new TLegend(0.1,0.8,0.3,0.9);
  leg->SetHeader("Momentum: 1GeV");
  leg->AddEntry(gr1,"Proton","l");
  leg->AddEntry(gr2,"Alpha","l");
  leg->Draw();
	
  canv.SaveAs("BB_proton_Alpha_in_Si.pdf");

  delete gr1;
  delete gr2;
  delete leg;

  // Exit
  return 0;
}
