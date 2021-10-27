/*Vector3D.cpp
  Sessione di laboratorio 1.b
  Progettare e implementare una classe C++ chiamata Vector3D per gestire operazioni matematiche che coinvolgono vettori di R^3*/

#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

void Acquisizione(double& x);

int main() {

  vector<Vector3D> vettore;
  double x, y, z;

  //Acquisizione delle coordinate cartesiane dei vettori da tastiera
  for(int i = 1; i < 3; i++) {
    cout<<"Inserire la coordinata x del vettore " << i << ": ";
    Acquisizione(x);
    cout<<"Inserire la coordinata y del vettore " << i << ": ";
    Acquisizione(y);
    cout<<"Inserire la coordinata z del vettore " << i << ": ";
    Acquisizione(z);
    vettore.push_back( Vector3D::Cartesiane(x,y,z) );
  }

  //Verifica corretta acquisizione dei dati usando il metodo iterativo dei vettori
  for( int j = 0; i < vettore.size(); i++) {
    cout << "vettore numero " << i << ": " << "\t vettore: { "
	 << vettore[i].getX() << ", "
	 << vettore[i].getY() << ", "
	 << vettore[i].getZ() << " }" << endl;
  }

  // Verifica funzionamento setters
  vettore.push_back( Vector3D::Cartesiane(0.,0.,0.) );
  cout << "\nProvo a inserire un vettore 1, 1, 1" << endl;
  vettore[2].setX(1.);
  vettore[2].setY(1.);
  vettore[2].setZ(1.);
  cout << "vettore numero 3" << "\t vettore: { "
       << vettore[2].getX() << ", "
       << vettore[2].getY() << ", "
       << vettore[2].getZ() << " }" << endl;

  // Verifica funzionamento member functions
  for(int i = 0; i < vettore.size(); i++) {
    cout << "\nVettore numero " << i << "\n"
	 << "Magnitudine: "     << vettore[i].magnitude()
	 << "\nTeta: "          << vettore[i].theta() << " rad o " << vettore[i].theta()*180/M_PI << " gradi"
	 << "\nPhi: "           << vettore[i].phi()   << " rad o " << vettore[i].phi()*180/M_PI   << " gradi" << endl;
  }

  // Verifica funzionamento Scalar Product
  double scalarProduct = vettore[0].scalarProduct(vettore[1]);
  cout << "Prodotto scalare="<< scalarProduct<<endl;

  // Verifica funzionamento Vector Product
  Vector3D vectorProduct = vettore[0].vectorProduct(vettore[1]);
  cout << "Prodotto vettoriale" << "\t vettore: { "
       << vectorProduct.getX() << ", "
       << vectorProduct.getY() << ", "
       << vectorProduct.getZ() << " }" << endl;

  // Verifica funzionamento angle
  double angle=vettore[0].angle(vettore[1]);
  cout << "Angle tra i due vettori= "<<angle<<" rad o " << angle*180/M_PI << " gradi"<<endl;
  cout << "Prova acos(): acos(1)= "<< acos(1.)<<endl;

  // Verifica funzionamento overload operators
  Vector3D v1 = vettore[0].operator+(vettore[1]);
  cout << "Somma tra due vettori= ";
  v1.print();
  Vector3D v2 = vettore[0].operator-(vettore[1]);
  cout << "Differenza tra due vettori= ";
  v2.print();
  Vector3D v4;
  v4.operator=(v1);
  v4.print();
  Vector3D v5 = vettore[0].operator*(3);
  v5.print();
  Vector3D v6 = vettore[0].operator/(0);
  v6.print();
  
  return 0;
}

void Acquisizione(double& x){
  while(!(cin>>x)){
    cout<<"ERRORE! Devi inserire un numero! Riprova: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
  }
}
