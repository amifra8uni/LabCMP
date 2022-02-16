/* Capacitor.cc
   Implementazione della classe Capacitor
   programma esame 11 febbraio 2022
   Francesco Amicucci 1795152      */

// Includo l'archivio d'intestazione (header) della classe
#include "Capacitor.h"
#define C_MIN 0
#define EPS_MIN 1
#define A_MIN 0
#define S_MIN 0

// Costrutttori
Capacitor::Capacitor() {                               // Predefinito
  name_ = "Senza nome";
  //C_ = 0; // Capacity [pF]
}
Capacitor::Capacitor(const Capacitor& capacitor) {     // Copia
  name_ = capacitor.name_;
  C_ = capacitor.C_;     
}
Capacitor Capacitor::Capacity(string name, double C) { // Named constructor idioms

  // Controllo che i valori inseriti non siano negativi o nulli
  Control(C, name, "la capacita' del condensatore", C_MIN);

  return Capacitor(name, C);
} 
Capacitor Capacitor::Component(string name, double epsr, double A, double s) {
  // A & s must have the same unit lenght
  double eps0 = 8.854; // pF/m

  // Controllo che i valori inseriti non siano negativi o nulli
  Control(epsr, name, "la costante dialettrica relativa", EPS_MIN);
  Control(A,    name, "l'area piatra del condensatore",   A_MIN);
  Control(s,    name, "la distanza di saparazione tra le piastre", S_MIN);
  
  return Capacitor(name, eps0*epsr*A/s);
}

// Distruttore
Capacitor::~Capacitor() { }

// Metodi di accesso - Getter Methods
string Capacitor::Name() const { return name_; }
double Capacitor::Cap()  const { return C_;    }
double Capacitor::C()    const { return C_;    }

// Metodi di aggiornamento - Setter Methods
void Capacitor::setC(double C)       { C_ = C; }
void Capacitor::setName(string name) { name_ = name; }

// Utility methods
void Capacitor::print() const {
  cout << "Il tuo condensatore " << name_
       << " ha capacita': " << C_ << " pF/m" << endl;
}

// Overload operators
Capacitor Capacitor::operator+(const Capacitor& rhs) const {
  double C = 1/(1/C_ + 1/rhs.C_); //sum of series capacitors
  return Capacitor(string("("+name_+"+"+rhs.name_+")"), C);
}
Capacitor Capacitor::operator||(const Capacitor& rhs) const {
  double C = C_ + rhs.C_; //sum of parallel capacitors
  return Capacitor("("+string(name_+"||"+rhs.name_+")"), C);
}
const Capacitor& Capacitor::operator=(const Capacitor& rhs) { // Assignment Operator
  // Non voglio che anche il nome venga copiato               // Non puo' essere costante
  C_ = rhs.C_;                                                // Stiamo modificando l'oggetto
  return *this; // Puntatore a se stesso
}
const Capacitor& Capacitor::operator+=(const Capacitor& rhs) {
  double C = 1/(1/C_ + 1/rhs.C_); //sum of series capacitors
  C_ = C;
  return *this;
}
/*const Capacitor& Capacitor::operator||=(const Capacitor& rhs) {
  double C = C_ + rhs.C_; //sum of parallel capacitors
  C_ = C;
  return *this;
}*/

// Funzioni globali - Non usata in app4.cpp
ostream& operator<<(ostream& os, const Capacitor& rhs){
  os << rhs.name_ << "\t" << rhs.C_; // NB: no endl!
  return os;
}

void Control(double &input, string name, string nome_variabile, double min) {
    while (input < min ) {
    cout << "\nAttenzione, problema con il condensatore " << name
	 << ", hai inserito un valore fisicamente sbagliato per " << nome_variabile
	 << "\nTi invitiamo a inserire un nuovo valore: ";
    cin >> input;
    while(cin.fail()) {
      cout << "Attenzione, devi inserire un numero, riprova: ";
      cin.clear();
      cin.ignore(1000, '\n');
      cin >> input;
    }
  }
}
