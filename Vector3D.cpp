/*Vector3D.cpp
  Sessione di laboratorio 1.b
  Progettare e implementare una classe C++ chiamata Vector3D per gestire operazioni matematiche che coinvolgono vettori di R^3*/

#include "Vector3D.h"
#include <iostream>
#include <cmath>
#include <limits>
#inclued <vector>

using namespace std;

void Acquisizione(double& x){
  while(!(cin>>x)){
    cout<<"ERRORE! Devi inserire un numero! Riprova: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
  }
}

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
    vettore.push_back( Vettore3D(x,y,z) );
  }

  //Verifica corretta acquisizione dei dati usando il metodo iterativo dei vettori
  int i = 0;
  for(Vector3D vettore_itr : vettore) {
    i++;
    cout << "vettore numero " << i << ": " << "\t vettore: { "
	 << vettore_itr.x() << ", "
	 << vettore_itr.y() << ", "
	 << vettore_itr.z() << " }" << endl;
  }

  // Verifica funzionamento setters
  vettore.push_back( vettore(0.,0.,0.) );
  cout << "provo a inserire un vettore 1,1,1" << endl;
  
  return 0;
}
