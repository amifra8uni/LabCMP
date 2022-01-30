#ifndef SpeedCALCULATOR_HH
#define SpeedCALCULATOR_HH

#include "Function.h"

class SpeedCalculator {

  public:
    SpeedCalculator() {
      integrand_ = 0;
    }
    void setIntegrand( Function* f ) {
        integrand_ = f;
    }
  vector<double> integrand(double x, double y) const {
    vector<double> foo;
    foo.push_back
        return integrand_->value(x);
    }

    Function* integrand() const {
        return integrand_;
    }
    virtual double velocity(double t0, double y0, double t) const = 0;

  private:
    Function* integrand_;

};
#endif
