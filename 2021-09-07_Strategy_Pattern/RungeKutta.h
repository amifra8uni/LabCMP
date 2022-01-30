#ifndef RungeKUTTA_HH
#define RungeKUTTA_HH

#include "SpeedCalculator.h"

class RungeKutta : public SpeedCalculator {

  public:
    RungeKutta(double h=0.1);
    void setDt( double h ) {
        dt_ = h;
    }
    virtual double velocity(double t0, double y0, double t) const;

  private:
    double dt_;
    //double uniform(double a, double b) const;
};
#endif
