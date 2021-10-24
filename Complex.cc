/* Complex.cc
Implementazione della classe Complex

Includo l'archivio d'intestazione della classe*/
#include "Complex.h"

//Includo tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>

using namespace std;

// constructor o costruttori
Complex::Complex() {                        // Predefinito - Default
  real_ = 0.;
  imag_ = 0.;
}                      
Complex::Complex(const Complex& complex) {  // Copia - Copy
  real_=complex.real_;
  imag_=complex.imag_;
}
// Named Constructor Idiom
Complex Complex::Polari(double r, double theta)       { return Complex(r*cos(theta), r*sin(theta)); }
Complex Complex::Cartesiane(double real, double imag) { return Complex(real, imag);                 }
 // Distruttore - Destructors
Complex::~Complex() { cout << "E' stato chiamato il distruttore per Complex " << real_ << " + " << imag_ << "i" << endl; }
//getters o funzioni d'accesso
double Complex::real() const { return real_; }
double Complex::imag() const { return imag_; }

//Redefinizione operatori - Overload operators
Complex Complex::operator+(const Complex& rhs) const{
  double re = real_ + rhs.real_; //sum of real values
  double im = imag_ + rhs.imag_; //sum of imaginary values
  return Complex(re,im);         //result of the sum
}

//Operator+ between Complex and double
Complex Complex::operator+(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex sum = Complex::operator+(Rhs);
  return sum;
}

Complex Complex::operator-(const Complex& rhs) const{
  double re = real_ - rhs.real_;  //subtraction of real values
  double im = imag_ - rhs.imag_;  //subtraction of imaginary values
  return Complex(re,im);          //result of the subtraction
}

//Operator- between Complex and double
Complex Complex::operator-(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex diff = Complex::operator-(Rhs);
  return diff;
}

Complex Complex::operator*(const Complex& rhs) const{
  double re = real_*rhs.real_-imag_*rhs.imag_; //real part
  double im = real_*rhs.imag_+imag_*rhs.real_; //imaginary part
  return Complex(re,im);                       //result of the multiplication
}

//Operator* between Complex and double
Complex Complex::operator*(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex molt = Complex::operator*(Rhs);
  return molt;
}

Complex Complex::operator/(const Complex& rhs) const{
  double re = (real_*rhs.real_+imag_*rhs.imag_)/(rhs.real_*rhs.real_+rhs.imag_*rhs.imag_);  // real part
  double im = (imag_*rhs.real_-real_*rhs.imag_)/(rhs.real_*rhs.real_+rhs.imag_*rhs.imag_);  // imaginary part
  return Complex(re,im);                                                                    // result of the division
}

//Operator between Complex and double
Complex Complex::operator/(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex dividi = Complex::operator/(Rhs);
  return dividi;
}

//Utility functions
void Complex::re() { cout << "The real part is: "      << real_ << endl; }
void Complex::im() { cout << "The imaginary part is: " << imag_ << endl; }
void Complex::r() {
  double r = sqrt(real_*real_+imag_*imag_);
  cout << "The module/magnitude is: " << r << endl;
}
void Complex::phi(){
  double phi = atan(imag_/real_);
  cout << "The phase is: " << phi << " rad" << " or " << phi*180/M_PI << " grades" << endl;
}
void Complex::mag()   { Complex::r()  ; }
void Complex::phase() { Complex::phi(); }

//setters o funzioni d'aggiornamento
void Complex::setReal(double real) { real_ = real; }
void Complex::setImag(double imag) { imag_ = imag; }
void Complex::print() { cout << "Numero complesso: " << real_ << " + " << imag_ << "i" << endl; }

