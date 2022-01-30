#ifndef DiffSpeed_h
#define DiffSpeed_h

#include <string>
#include "Function.h"

class DiffSpeed : public Function {
  public:
    DiffSpeed(const std::string& name, double beta, double m);

    virtual double value(double x) const;
    virtual void print() const;

  private:
    double beta_;
    double m_;
};
#endif
