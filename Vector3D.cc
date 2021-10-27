//Includo l'archivio header della classe
#include "Vector3D.h"

//Includo gli archivi aggiuntivi necessari
#include <iostream>
#include <cmath>
using namespace std;

//Costruttori o constructors
Vector3D::Vector3D(){ // Predefinito - Default
  x_=0.;
  y_=0.;
  z_=0.;
}
Vector3D::Vector3D(const Vector3D& vector3D) { // Copia - Copy
  x_=vector3D.x_;
  y_=vector3D.y_;
  z_=vector3D.z_; 
}
// Named Constructor Idiom
Vector3D Vector3D::Sferiche(double r, double theta, double phi)       { return Vector3D(r*sin(theta)*cos(phi),r*sin(theta)*sin(phi), r*cos(theta)); }
Vector3D Vector3D::Cartesiane(double x, double y, double z) { return Vector3D(x, y, z);           
}

//Getters
double Vector3D::getX() const {return x_;} //Restituisce la coordinata x
double Vector3D::getY() const {return y_;} //Restituisce la coordinata y
double Vector3D::getZ() const {return z_;} //Restituisce la coordinata z

//Utility functions
double Vector3D::magnitude(){
  double magnitude = sqrt(x_*x_+y_*y_+z_*z_);
  return magnitude;
}
double Vector3D::phi(){
  double phi = acos(z_/Vector3D::magnitude());
  return phi;
}
double Vector3D::theta(){
  double theta = asin(y_/Vector3D::magnitude()*sin(Vector3D::phi()));
  return theta;
}

//Member functions
double Vector3D::scalarProduct(const Vector3D& rhs){
  double scalarProduct=0.;
  scalarProduct = x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
  return scalarProduct;
}

//Setters
void Vector3D::setX(double x) { x_=x; }
void Vector3D::setY(double y) { y_=y; }
void Vector3D::setZ(double z) { z_=z; }
