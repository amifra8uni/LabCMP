/*Vector3D.cc
  Includo l'archivio header della classe*/

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
void Vector3D::print(){
  cout<< "vettore : { "
      << x_<< ", "
      << y_ << ", "
      << z_ << " }" << endl;
}


//Member functions
double Vector3D::scalarProduct(const Vector3D& rhs){
  double scalarProduct=0.;
  scalarProduct = x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
  return scalarProduct;
}

Vector3D Vector3D::vectorProduct(const Vector3D& rhs){
  double x,y,z;
  x = y_*rhs.z_-z_*rhs.y_;
  y = z_*rhs.x_-x_*rhs.z_;
  z = x_*rhs.y_-y_*rhs.x_;
  Vector3D vector = Vector3D::Cartesiane(x,y,z);
  return vector;
}

double Vector3D::angle(const Vector3D& rhs){
  double angle=0.;
  double u=0., v=0.;
  Vector3D vector = rhs;
  u = Vector3D::magnitude();
  v = vector.magnitude();
  if(u==0 || v==0){
    cout<<"ATTENZIONE! Non puoi calcolare l'angolo con un vettore nullo! Verrà restituito un angolo nullo"<<endl;
  }
  else{
  angle = acos((Vector3D::scalarProduct(rhs))/(u*v));
  }
  return angle; 
}

//Overload operators
Vector3D Vector3D::operator+(const Vector3D& rhs) const{
  double x = x_ + rhs.x_; //sum of x coordinates
  double y = y_ + rhs.y_; //sum of y coordinates
  double z = z_ + rhs.z_; //sum of z coordinates
  return Vector3D(x,y,z);
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const{
  double x = x_ - rhs.x_; //difference of x coordinates
  double y = y_ - rhs.y_; //difference of y coordinates
  double z = z_ - rhs.z_; //difference of z coordinates
  return Vector3D(x,y,z);
}

const Vector3D Vector3D::operator=(const Vector3D& rhs) {
  x_ = rhs.x_;
  y_ = rhs.y_;
  z_ = rhs.z_;
  return *this;
}

Vector3D Vector3D::operator*(const double& rhs) const{
  return Vector3D(x_*rhs,y_*rhs,z_*rhs);
}
Vector3D Vector3D::operator/(const double& rhs) const{
  Vector3D foo = Vector3D::Cartesiane(x_,y_,z_);
  if(rhs==0.){
    cout<<"ATTENZIONE! Non puoi dividere per zero! L'operazione verrà ignorata"<<endl;
  }
  else{
    foo.setX(x_/rhs);
    foo.setY(y_/rhs);
    foo.setZ(z_/rhs);
  }
  return foo;
}

//Setters
void Vector3D::setX(double x) { x_=x; }
void Vector3D::setY(double y) { y_=y; }
void Vector3D::setZ(double z) { z_=z; }


