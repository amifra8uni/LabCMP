//Vector3D.h header della classe Vector3D

class Vector3D {

 public:

  //Constructors
  Vector3D(); //Default
  Vector3D(const Vector3D& vector3D); //Copy

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

 private:

  double x_;
  double y_;
  double z_;
};
