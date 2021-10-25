//Vector3D.h header della classe Vector3D

class Vector3D {

 public:

  //Constructors
  Vector3D(); //Default
  Vector3D(const Vector3D& vector3D); //Copy
  Vector3D(double x, double y,double z); //Regular

  //Getters
  double getX() const;
  double getY() const;
  double getZ() const;
  
  //Setters
  void setX(double x);
  void setY(double y);
  void setZ(double z);

  //Utility functions
  double magnitude();
  double phi();
  double theta();

  //Member functions
  double scalarProduct(const Vector3D& rhs); //AOOOOOO
  

 private:

  double x_;
  double y_;
  double z_;

};
