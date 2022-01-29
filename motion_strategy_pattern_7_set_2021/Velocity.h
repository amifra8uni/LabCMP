//Velocity.h

#ifndef Velocity_h
#define Velocity_h

class Velocity {
public:
  // constructors
  Velocity() {
    vx_=0;
    vy_=0;
  }
  Velocity(double vx, double vy);

  // destructor
  ~Velocity() {}

  // getters
  double Vx() const;
  double Vy() const;

  // setters
  void setVx(double vx);
  void setVy(double vy);

  // print method
  void print() const;

  // overload operators
  Velocity operator+(const Velocity& rhs);
  const Velocity& operator=(const Velocity& rhs);

private:
  double vx_;
  double vy_;
};
#endif
