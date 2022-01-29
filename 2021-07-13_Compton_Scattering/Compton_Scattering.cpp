/*Decadimento_Fra.cpp
  Simulazione della diffusione Compton di un fotone*/

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
#include "TF1.h"

#define ME 511 // KeV/c^2
using namespace std;

double E_Compton(double Ei, double theta);

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
  
  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(time(NULL));

  // Un altro generatore per la distribuzione di numeri casuali
  TF1* f1 = new TF1("f1", "1+cos(x)*cos(x)", 0, M_PI);

  double E0 = 662; // KeV
  double res = 0.025;

  // Istogrammi per salavare i dati (name, title, number of bins, range)
  TH1F hangle("hangle", "distribuzione dei cos(theta) generati", 200, -1, 1);
  TH1F hcosangle("hangle", "distribuzione dei cos(theta) generati", 200, -1, 1);
  TH1F hcompDiff("hcomptDiff", "Distribuzione dell'energia dei fotoni diffusi", 300, 0, E0*(1+10*res)+15);  
  TH1F hcompTot("hcomptDiff", "Distribuzione dell'energia di tutti i fotoni", 300, 0,  E0*(1+10*res)+15);  
   
  
  for(int i = 0; i < 1000000; i++) {
    int prob = gen->Integer(101);
    double Emis;
    //cout << "y vale :" << prob << endl;

    // Decido con una probabilità del 65% se il fotone subisce diffusione
    if (prob <= 65) {
      // Estraggo il valore dell'angolo generato da una distribuzione personalizzata
      double theta = f1->GetRandom();
      hangle.Fill(cos(theta));

      // Calcolo il valore dell'energia del fotone dopo la diffusione
      double Ef = E_Compton(E0, theta);
      // Calcolo il valore misurato tenendo contro dells risoluzione del rivelatore
      Emis = gen -> Gaus(Ef, Ef*res);
      hcompDiff.Fill(Emis);
      hcompTot.Fill(Emis);
    }
    // Se il fotone non subisce diffusione salvo il valore dell'energia iniziale
    else {
      Emis = gen -> Gaus(E0, E0*res);
      hcompTot.Fill(Emis);
    }
  }

  // After generating the data, we take care of plotting the results:
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  // * start from TRUE values and customize some histogram properties
  hangle.GetXaxis()->SetTitle("cos(theta)");
  hangle.GetYaxis()->SetTitle("cos(theta)/(1/200)");
  // * plot
  hangle.Draw();
  // * store to file in 2 formats
  canv.SaveAs("./costheta.pdf");
  canv.SaveAs("./costheta.jpg");

  // Spostiamoci all'energia dei fotoni diffusi
  hcompDiff.GetXaxis()->SetTitle("E [KeV]");
  hcompDiff.GetYaxis()->SetTitle("Numero di eventi/Ampiezza bin)");
  // * plot
  hcompDiff.Draw();
  // * store to file in 2 formats
  canv.SaveAs("./compton-truth-diff.pdf");
  canv.SaveAs("./compton-truth-diff.jpg");

  // Spostiamoci all'energia di tutti i fotoni
  // Anche i non diffusi
  hcompTot.GetXaxis()->SetTitle("E [KeV]");
  hcompTot.GetYaxis()->SetTitle("Numero di eventi/Ampiezza bin)");
  // * plot
  hcompTot.Draw();
  // * store to file in 2 formats
  canv.SaveAs("./compton-truth.pdf");
  canv.SaveAs("./compton-truth.jpg");
  
  // Store both histograms to file
  hangle.Write();
  hcompDiff.Write();
  hcompTot.Write();

  // Critical to close the file!
  rfile.Close();

  // Delete the random generator
  delete gen;
  delete f1;
  
  return 0;
  
}

double E_Compton(double Ei, double theta) {
  double Ef = Ei / (1 + Ei*(1-cos(theta))/ME);
  return Ef;
}
