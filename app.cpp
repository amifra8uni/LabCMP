/* app.cpp
   programma di prova */

// Includo l'archivio di intestazione
#include <iostream>
#include <cmath>

//#include "Particle.h"
#include "Material.h"

//Archivio di intestazione di ROOT: grafici, salvataggio
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"

using namespace std;
#define N 10
#define A 28
#define Z 14
#define RHO 2.33
#define I 173
#define DELTA 0

int main() {

Particle alpha(3.7, 2, 1);
Particle proton(0.938, 1, 1);
Material silicon(RHO, A, Z, I);

/*
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
*/
double x[N], yp[N], yalpha[N];

//definisco il passo della mia funzione
double dx = 0.1; // cm

for (int i=0; i<N; i++) {

// Definisco le mie variabili di appoggio
double dEa, dEp, EProtoVecchia, EAlphaVecchia;

// Calcolo la perdita di energia per le due particelle
dEp = silicon.dEdx(proton, DELTA);
dEa = silicon.dEdx(alpha, DELTA);

// Salvo i dati per il grafico
x[i]  = i*dx;
yp[i] = dEp;
yalpha[i] = dEa;
cout << "Valore di x[i] = "<< x[i] << endl;
// Aggiorno il trimomento della particelle dopo la perdita di energia
EProtoVecchia = sqrt(proton.p()*proton.p() + (proton.m()*proton.m()));
EAlphaVecchia = sqrt(alpha.p()*alpha.p() + (alpha.m()*alpha.m()));
proton.setP(sqrt( (EProtoVecchia - dEp*dx)*(EProtoVecchia - dEp*dx) - proton.m()*proton.m()));
alpha.setP(sqrt( (EAlphaVecchia - dEp*dx)*(EAlphaVecchia - dEp*dx) - alpha.m()*alpha.m()));
}
cout << "Ultimo valore di x[N-1] = "<< x[N-1] << endl;
// create graph
TGraph gr(N,x,yp);
TCanvas canv1("canv", "canvas for plotting", 1280, 1024);
canv1.SetGrid();

// draw the graph with axis, continuous line, and put
// a * at each point
gr.SetTitle("Energia persa per un protone di 10 MeV nel silicio");
gr.Draw("AC*");
canv1.SaveAs("./BB_proton_in_Si.pdf");

// After generating the data, we take care of plotting the results:
// * create canvas
//TCanvas canv("canv", "canvas for plotting", 1280, 1024);

// Chiudo il file
//rfile.Close();

// Exit
return 0;
}
