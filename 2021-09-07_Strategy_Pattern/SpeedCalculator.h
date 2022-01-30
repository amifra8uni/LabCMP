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
    double integrand(double x) const {
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
