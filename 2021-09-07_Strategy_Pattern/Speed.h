#ifndef Speed_h
#define Speed_h

#include <string>
#include "Function.h"

class Speed : public Function {
  public:
    Speed(const std::string& name, double beta, double m);

    virtual double value(double x) const;
    virtual void print() const;

  private:
    double beta_;
    double m_;
};
#endif
