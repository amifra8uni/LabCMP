//RungeKutta.h

#ifndef RungeKutta_h
#define RungeKutta_h

#include "SpeedCalculator.h"
#include "Velocity.h"

#include <vector>

using std::vector;

class RungeKutta : public SpeedCalculator {
public:
  RungeKutta(Velocity v0, double beta, double m, double g, double h);
  ~RungeKutta() {}

  virtual vector<Velocity> velocity(double tmin, double tmax) const;

private:
  double h_;
};
#endif
