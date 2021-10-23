/* Complex.cc
Implementazione della classe Complex

Includo l'archivio header della classe*/
#include "Complex.h"

//Includo tutti gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>
using namespace std;

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

/* Named Constructor Idiom
static Complex Polar(double r, double theta){
  return Complex(r*cos(theta),r*sin(theta));
}
static Complex Cartesian(double x, double y){
  return Complex(x,y);
  }
*/

//Overload operators
Complex Complex::operator+(const Complex& rhs) const{
  //sum of real values
  double re = real_ + rhs.real_;
  //sum of imaginary values
  double im = imag_ + rhs.imag_;
  //result of the sum
  return Complex(re,im);
}

//Operator+ between Complex and double
Complex Complex::operator+(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex sum = Complex::operator+(Rhs);
  return sum;
}

Complex Complex::operator-(const Complex& rhs) const{
  //subtraction of real values
  double re = real_ - rhs.real_;
  //subtraction of imaginary values
  double im = imag_ - rhs.imag_;
  //result of the subtraction
  return Complex(re,im);
}

//Operator- between Complex and double
Complex Complex::operator-(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex diff = Complex::operator-(Rhs);
  return diff;
}

Complex Complex::operator*(const Complex& rhs) const{
  //real part
  double re = real_*rhs.real_-imag_*rhs.imag_;
  //imaginary part
  double im = real_*rhs.imag_+imag_*rhs.real_;
  //result of the multiplication
  return Complex(re,im);
}

//Operator* between Complex and double
Complex Complex::operator*(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex molt = Complex::operator*(Rhs);
  return molt;
}

Complex Complex::operator/(const Complex& rhs) const{
  //real part
  double re = (real_*rhs.real_+imag_*rhs.imag_)/(rhs.real_*rhs.real_+rhs.imag_*rhs.imag_);
  //imaginary part
  double im= (imag_*rhs.real_-real_*rhs.imag_)/(rhs.real_*rhs.real_+rhs.imag_*rhs.imag_);
  //result of the division
  return Complex(re,im);
}

//Operator between Complex and double
Complex Complex::operator/(const double& rhs) const{
  Complex Rhs(rhs,0);
  Complex dividi = Complex::operator/(Rhs);
  return dividi;
}

//Utility functions
void Complex::re(){
  cout<< "The real part is: "<<real_<<endl;
}

void Complex::im(){
  cout<< "The imaginary part is: "<<imag_<<endl;
}

void Complex::r(){
  double r=sqrt(real_*real_+imag_*imag_);
  cout<< "The module/magnitude is: "<<r<<endl;
}

void Complex::phi(){
  double phi=atan(imag_/real_);
  cout<< "The phase is: "<<phi<<" rad"<<" or "<<phi*180/M_PI<<" grades"<<endl;
}

void Complex::mag(){
  Complex::r();
}

void Complex::phase(){
  Complex::phi();
}

//getters o funzioni d'accesso
double Complex::real() { return real_; }
double Complex::imag() { return imag_; }

//setters o funzioni d'aggiornamento
void Complex::setReal(double real) { real_ = real; }
void Complex::setImag(double imag) { imag_ = imag; }

void Complex::print() {
  cout << "Numero complesso: " << real_ << " + " << imag_ << "i" << endl;
}

