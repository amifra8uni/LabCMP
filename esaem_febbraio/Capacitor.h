/* Capacitor.h
   Dichiarazione della classe
   Archivio di intestazione (header) della classe Capacitor
   programma esame 11 febbraio 2022
   Francesco Amicucci 1795152      */

#ifndef Capacitor_h // Evita che g++ si lamenti
#define Capacitor_h // nel caso venisse incluso piu' volte

//Includo gli archivi aggiuntivi necessari
#include <iostream>
#include <string>

using namespace std;

class Capacitor {

 public:

  // Costrutttori - NOTA: no return
  Capacitor();                                                               // Predefinito
  Capacitor(const Capacitor& capacitor);                                     // Copia
  static Capacitor Capacity(string name, double C);                          // Named Constructor Idiom
  static Capacitor Component(string name, double eps, double A, double s);   /* Static member functions of a class 
                                                                                can be called without having any 
  // Distruttore                                                                object of the class               */
  ~Capacitor();

  // Metodi di accesso - Accessors o Getter Methods
  string Name() const;
  double Cap()  const;
  double C()    const;

  // Metodi di aggiornamento - Setter Methods
  void setName(string name);
  void setC(double C);
  
  // Utility method
  void print() const;

  // Overload operators
  Capacitor operator+(const Capacitor& rhs)  const;
  Capacitor operator||(const Capacitor& rhs) const;
  const Capacitor& operator=(const Capacitor& rhs);  // Assignment Operator
  const Capacitor& operator+=(const Capacitor& rhs); // non puo' essere costante
  //const Capacitor& operator||=(const Capacitor& rhs); // stiamo modificando l'oggetto
  
  // Overloading an operator as Global Functions declared friend
  // (ossia dovrebbe stare fuori dallo scope della classe) 
  friend ostream& operator<<(ostream& os, const Capacitor& rhs); // Non usata

  
 private:

  // Attributi o Data members
  double C_;
  string name_;
  
  // Costruttore regolare
  Capacitor(string name, double C) { 
    C_ = C;
    name_ = name; 
  };
  
};

// Funzione globale
void Control(double &, string, string, double);
#endif
