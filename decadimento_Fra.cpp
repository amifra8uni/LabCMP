/*Decadimento_Fra.cpp
  Simulazione del decadimento di una particella in due particelle di massa minore*/

//Includo l'archivio di intestazione standard e quelli aggiuntivi
#include <iostream>
#include <cmath>

//Archivio di intestazione di ROOT: numeri casuali, grafici, salvataggio
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "Vector3D.h"

using namespace std;

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // Apri TFile per l'output
  TString rootfname("./output.root");
  // Sovrascrivi l'archivio di output se dovesse già esistere
  TFile rfile(rootfname, "RECREATE");
  /* Apri il l'archivio ROOT e mi assicuro che sia stato aperto con successo.
     Cause tipiche di non riuscita sono: 1) percorso sbagliato 2) mancanza privilegi di scrittura
     Typical cause for failure are: 1) wrong path, 2) no write privilege */
  if( !rfile.IsOpen() ) {
    std::cout << "Problemi creando l'archivio ROOT. Esistendo... \nProblems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "Memorizzando l'output in un archivio ROOT \nStoring output in root file " << rootfname << std::endl;

  /*Con un generatore di numeri casuali, vogliamo
    1) Generale il VALORE VERO dell'osservabile in un determinato intervallo e poi
    2) Tener contro della risuluzione del rivelatore per generale il VALORE MISURATO da quest'ultimo */
  // With a random generator, we want to
  // 1) generate the TRUE VALUE of the observable in a given range and then
  // 2) take into account the detector resolution to generate the
  //    VALUE MEASURED by the detector

  // Genero un vettore uniformemente distribuito sulla superficie di una sfera unitaria
double x,y,z;
  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom3*  gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);
gen.Sphere(&x, &y, &z, 1);
cout << "{x, y, z} = { "<< x << y << z << " }" <<endl;

  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Critical to close the file!
  rfile.Close();

  // Exit
  return 0;
}
