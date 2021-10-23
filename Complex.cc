/* Complex.cc
Implementazione della classe Complex

Includo l'archivio header della classe*/
#include "Complex.h"

//Includo tutti gli archivi aggiuntivi necessari
#include <iostream>
using std::cout;
using std::endl;

// constructor o costruttori
Complex::Complex() { }
Complex::Complex(double real, double imag) {
  real_=real;
  imag_=imag;
}
Complex::Complex(const Complex& complex) {
  real_=complex.real_;
  imag_=complex.imag_;
}

//getters o funzioni d'accesso
double Complex::real() { return real_; }
double Complex::imag() { return imag_; }

//setters o funzioni d'attualizzamento
void Complex::setReal(double real) { real_ = real; }
void Complex::setImag(double imag) { imag_ = imag; }

void Complex::print() {
  cout << "Numero complesso: " << real_ << " + " << imag_ << "i" << endl;
}

