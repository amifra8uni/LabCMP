/*Vector.cpp
  Sessione di laboratorio 1.b
  Progettare e implementare una classe C++ chiamata Vector3D per gestire operazioni matematiche che coinvolgono vettori di R^3*/

#include "Vector.h"
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

void Acquisizione(double& x){
  while(!(cin>>x)){
    cout<<"ERRORE! Devi inserire un numero! Riprova: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
  }
}

int main() {

  Vector v1 = Complex::Cartesiane(0,0);
  Vector c2 = Complex::Polari(0,0);
  double x1,y1,x2,y2;

  cout<<"Inserire parte reale del primo numero: ";
  Acquisizione(x1);
  c1.setReal(x1);
  cout<<"Inserire parte immaginaria del primo numero: ";
  Acquisizione(y1);
  c1.setImag(y1);
  c1.print();

  cout<<"Inserire parte reale del secondo numero: ";
  Acquisizione(x2);
  c2.setReal(x2);
  cout<<"Inserire parte immaginaria del secondo numero: ";
  Acquisizione(y2);
  c2.setImag(y2);
  c2.print();

  Complex c=c1+c2;
  cout<<"Somma dei due numeri: c1+c2 = "<< c.real() << " + "<<c.imag() <<"i"<<endl;
  c=c1-c2;
  cout<<"Differenza dei due numeri: c1-c2 = "<< c.real() << " + "<<c.imag() <<"i"<<endl;

  c=c1*c2;
  cout<<"Prodotto dei due numeri: c1*c2 = "<< c.real() << " + "<<c.imag() <<"i"<<endl;

  c=c1/c2;
  cout<<"Divisione tra i due numeri: c1/c2 = "<< c.real() << " + "<<c.imag() <<"i"<<endl; 

  return 0;
}
