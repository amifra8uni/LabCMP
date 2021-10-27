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
  int i = 0;
  for(Vector3D vettore_itr : vettore) {
    i++;
    cout << "vettore numero " << i << ": " << "\t vettore: { "
	 << vettore_itr.getX() << ", "
	 << vettore_itr.getY() << ", "
	 << vettore_itr.getZ() << " }" << endl;
  }

  // Verifica funzionamento setters
  vettore.push_back( Vector3D(0.,0.,0.) );
  cout << "\nProvo a inserire un vettore 1, 1, 1" << endl;
  vettore[2].setX(1.);
  vettore[2].setY(1.);
  vettore[2].setZ(1.);
  cout << "vettore numero 3" << "\t vettore: { "
       << vettore[2].getX() << ", "
       << vettore[2].getY() << ", "
       << vettore[2].getZ() << " }" << endl;

  // Verifica funzionamento member functions
  i = 0;
  for(Vector3D vettore_itr : vettore) {
    i++;
    cout << "\nVettore numero " << i << "\n"
	 << "Magnitudine: "     << vettore_itr.magnitude()
	 << "\nTeta: "          << vettore_itr.theta() << " rad o " << vettore_itr.theta()*180/M_PI << " gradi"
	 << "\nPhi: "           << vettore_itr.phi() << " rad o " << vettore_itr.phi()*180/M_PI << " gradi" << endl;
  }
  return 0;
}

void Acquisizione(double& x){
  while(!(cin>>x)){
    cout<<"ERRORE! Devi inserire un numero! Riprova: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
  }
}
