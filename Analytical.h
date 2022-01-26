//Analytical.h

#ifndef Analytical_h
#define Analytical_h

#include "Velocity.h"
#include "SpeedCalculator.h"

#include <vector>

using std::vector;

class Analytical : public SpeedCalculator {
public:
  Analytical(Velocity v0, double beta, double m, double g, double dt);
  ~Analytical() {}

  virtual vector<Velocity> velocity(double tmin, double tmax) const;

private:
  double dt_;
};
#endif
