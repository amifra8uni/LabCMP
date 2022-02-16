/* app4.cpp                          
   programma esame 11 febbraio 2022
   Francesco Amicucci 1795152      */
 
// Includo gli archivi di intestazione
#include <fstream>  // Per l'output dei file
#include <iomanip>  // Per setPrecision
#include <iostream> // Per lo standar input/output: cin, cout, cerr
#include <string>
#include <stdlib.h> // per usare lrand48 e EXIT_FAILURE
#include <time.h>   // per inizializzare il seme di lrand

// Includo gli archivi per le mie classi
#include "Capacitor.h"

using namespace std;

// Definisco delle costanti con delle direttive al precompilatore
#define C1MAX 100
#define LEN 30
#define C2 10 // pF = e-12 Farad
#define C3 5
#define C4 15
#define N 1e3 // Numero di eventi da generare

int main() {

  // Inizializzo il seme per il generaore di numeri casuali
  srand48(time(0)); // Mai dentro una funzione!

  // Costruisco i miei 4 condensatori
  Capacitor Cap1;
  Cap1.setName("C1");
  Capacitor Cap2 = Capacitor::Capacity("C2", C2);
  Capacitor Cap3 = Capacitor::Capacity("C3", C3);
  Capacitor Cap4 = Capacitor::Capacity("C4", C4);
  Capacitor Ceq;
  Ceq.setName("Ceq");
  
  // ** OUTPUT**
  ofstream ofile("./true.dat");
  string ofnam("./true.dat");
  cout << "Crando una cartella di output chiamata " << ofnam << endl;
  //ofile.open(ofnam); // Non funziona nella macchina virtuale

  // Stampo la prima riga del file di output
  ofile << "#C1" << "\t" << "#Ceq"  << endl;

  const char filename[LEN] = "./Python_C1.dat"; // Nome del file di input
  
#ifdef CON_INPUT  // INPUT SOLO SE NECESSARIO

  ifstream infile(filename); // Create Input file object
  string line;               // String to hold each line

  // Make sure input file is open otherwise exit
  if(!infile.is_open()) {
    cerr << "Non risco ad aprire il file di input"
	 << "\nAssicurati di averlo chiamato: " << filename << endl;
    exit(EXIT_FAILURE);
  }
  
  // Loop dell'archivio fino alla fine
  while(!infile.eof()) {
    // get current line
    getline(infile, line);
    if( line == "\n" || line == "" ) continue;

    // parse line with the provided format and put data in variables
    // NB: USING POINTERS TO VARIABLES
    // format:  %s string    %f  float   %lf  double
    double C1;
    sscanf(line.c_str(),"%lf", &C1);

    // print out for debug purposes
    //cout << "C1: " << C1 << endl;

    Cap1.setC(C1);
    Ceq = (Cap1||Cap2)+(Cap3||Cap4); // Uso l'operatore = che non ho scritto all'esame
    
    ofile << C1 << "\t"  // Salvo i valori su file
	  << Ceq.C() << endl;
  } // !eof

  // close input file before exiting
  infile.close();
  
#endif

  
#ifndef CON_INPUT
  
  cout << "Hai scelto far generare direttamente al programma i valori casuali di C1 nell'intervallo [1,100] pF"
       << "\nSe preferisci usare altri dati, puoi fornirli in un file chiamato " << filename
       << "\nRicordati in tal caso di aggiungere l'opzione -DCON_INPUT in fase di compilazione del programma" << endl;
  
  // Ciclo per generare gli eventi
  for (int i = 0; i < N; i++) {
    double C1 = (double) lrand48() / RAND_MAX * (C1MAX - 1)  + 1;
    Cap1.setC(C1);
    Ceq = (Cap1||Cap2)+(Cap3||Cap4);
    // Salvo i valori
    ofile << C1 << "\t"       // Nota: non uso l'operatore <<
	  << Ceq.C() << endl; //       perche' non sono interessato al nome
  }
  
#endif

  ofile.close();  // close output file before exiting
  cout << "Dati salvati su " << ofnam << " con successo."<< endl;
  
  return 0;      // exit
}
