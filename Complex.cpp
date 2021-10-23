/*Complex.cpp
  Archivio per vedere se funziona la classe Complex*/

#include "Complex.h"
#include <iostream>
#include <cmath>
using namespace std;

int main() {

  Complex c1(3,4);
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

  Complex c7=c1.operator+(7.);
  cout<<"\nInformazioni su c7"<<endl;
  c7.print();

  return 0;
}
