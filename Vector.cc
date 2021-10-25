//Includo l'archivio header della classe
#include "Vector.h"

//Includo gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>
using namespace std;

//Constructors
Vector3D::Vector3D(double x, double y, double z){ //Default
  x_=0.;
  y_=0.;
  z_=0.;
}
Vector3D::Vector3D(const Vector3D& vector) { //Copy
  x_=vector.x_;
  y_=vector.y_;
  z_=vector.z_;
}

//Getters
double Vector3D::xcord() const {return x_;} //Restituisce la coordinata x
double Vector3D::ycord() const {return y_;} //Restituisce la coordinata y
double Vector3D::zcord() const {return z_;} //Restituisce la coordinata z

//Utility functions
double Vector3D::magnitude(){
  double magnitude = sqrt(x_*x_+y_*y_+z_*z_);
  return magnitude;
}
double Vector3D:phi(){
  double phi = acos(z_/Vector3D::magnitude());
}
