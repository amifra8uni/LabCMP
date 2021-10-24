/*Complex.cpp
  Archivio per vedere se funziona la classe Complex*/

#include "Complex.h"
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

  Complex c1 = Complex::Cartesiane(0,0);
  Complex c2 = Complex::Polari(0,0);
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

  /*Complex c1(3,4);
  cout<<"Informazioni su c1"<<endl;
  c1.print();

  c1.setReal(6);
  c1.setImag(8);
  c1.print();

  Complex c2(5,5);
  cout<<"\nInformazioni su c2"<<endl;
  c2.print();
  //c2.re();
  //c2.im();
  //c2.mag();
  //c2.phase();

  Complex c3=c1.operator+(c2);
  cout<<"\nInformazioni su c3"<<endl;
  c3.print();
  //c3.re();
  //c3.im();
  //c3.mag();
  //c3.phase();
  c3 = c1 + c2;
  c3.print();

  Complex c4=c1.operator-(c2);
  cout<<"\nInformazioni su c4"<<endl;
  c4.print();

  Complex c5=c1.operator*(c2);
  cout<<"\nInformazioni su c5"<<endl;
  c5.print();

  Complex c6=c1.operator/(c2);
  cout<<"\nInformazioni su c6"<<endl;
  c6.print();

  Complex c7=c1.operator/(7.);
  cout<<"\nInformazioni su c7"<<endl;
  c7.print();*/

  return 0;
}
