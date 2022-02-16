/* app2.cpp                          
   programma esame 11 febbraio 2022
   Francesco Amicucci 1795152      */
 
// Includo gli archivi di intestazione
#include <fstream> // Per l'output dei file
#include <iomanip> // Per setPrecision
#include <iostream>
#include <string>
#include <stdio.h>

// Includo gli archivi per le mie classi
#include "Capacitor.h"

using namespace std;

#define CAP 1
#define A 0.1
#define S 0.1
#define EPSR 1.5

int main() {

  // Funzionamento costruttori
  Capacitor C_Pred;
  cout << "Questo è un condensatore creato con un costruttore predefinito, regolare e copia: " << endl;
  C_Pred.print();
  Capacitor C_Reg = Capacitor::Capacity("C_Reg", CAP);
  C_Reg.print();
  Capacitor C_Copy = C_Reg;
  C_Copy.print();
  
  cout << "Usando un metodo di accesso so che la capacita' del condensatore " << C_Reg.Name() << " e': " << C_Reg.C() << " pF/m" << endl;

  cout << "\nAdesso la aggiorno a 10 pF/m" << endl;
  C_Reg.setC(10);
  C_Reg.print();

  cout << "\nAdesso provo a sommare in serie due volte lo stesso condensatore" << endl;
  Capacitor C_ser = C_Reg+C_Reg; // C_Reg.operator+( C_Reg );
  C_ser.print();
  
  cout << "\nStessa cosa, ma con l'operatore +=" << endl;
  C_Reg += C_Reg;
  C_Reg.print();
  C_Reg.setC(10);
  
  cout << "\nOra in parallelo" << endl;
  Capacitor C_par = C_Reg||C_Reg; // C_Reg.operator||( C_Reg );
  C_par.print();

  /*cout << "\nStessa cosa, ma con l'operatore ||=" << endl;
  C_Reg ||= C_Reg;
  C_Reg.print();
  C_Reg.setC(10);*/
  
  cout << "\nOra lo uguaglio a C_reg con l'operatore =" << endl;
  C_Reg.print();
  C_par = C_Reg;
  C_par.print();

  cout << "\nUsando i named constructed idioms, posso creare un condensatore anche a partire dalle sue componenti"
       << "\nPer esempio scelgo A = 0.1 m^2, s = 0.1 m e eps_r = 1.5" << endl;
  
  Capacitor C_Comp = Capacitor::Component("C_comp", EPSR, A ,S);
  C_Comp.print();

  cout << "\nCosa succede se inserisco delle componenti senza senso fisico?"
       << "\nPer esempio  A = -10 m^2, s = -1 m e eps_r = 0.5" << endl;
  Capacitor C_err = Capacitor::Component("C_errore", 0.5, -10 , -1);
  C_err.print();

  cout << "\nQuesta e' una prova di stampa usando l'operatore <<: "
       << C_Reg << endl;

  cout << "\nPosso anche definire il mio oggetto con un puntatore come: Capacitor* C_Reg = new Capacitor::Capacity(\"C_Reg\", CAP);"
       << "\nIn tal caso mi devo ricordare di mettere un \"delete\" C_reg alla fine" << endl;
  Capacitor* C_Reg2 = new Capacitor; // allocaione memoria
  C_Reg2->print(); // Use -> instead of . with pointers to objects
  
  delete C_Reg2;   // disallocazione della memoria
    
  return 0; // exit
}
