//Vector3D.h header della classe Vector3D

class Vector3D {

 public:

  //Constructors
  Vector3D(); //Default
  Vector3D(const Vector3D& vector3D); //Copy
  //Named Constructor Idiom
  static Vector3D Sferiche(double r,double theta, double phi);
  static Vector3D Cartesiane(double x, double y, double z);

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
  
//Costruttore regolare - regular constructor
  Vector3D(double x, double y, double z) {
    x_ = x;
    y_ = y;
    z_ = z;
  };
};
