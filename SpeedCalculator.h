//SpeedCalculator.h

#ifndef SpeedCalculator_h
#define SpeedCalculator_h

#include "Velocity.h"
#include <vector>

using std::vector;

class SpeedCalculator {
public:
  SpeedCalculator(Velocity v0, double beta, double m, double g) {
    v0_=v0;
    beta_=beta;
    m_=m;
    g_=g;
  }

  // Setters - Metodi di aggiornamento
  virtual void setVelocity(Velocity v0) { v0_=v0; }
  virtual void setBeta(double beta) { beta_=beta; }
  virtual void setM(double m) { m_=m; }
  virtual void setG(double g) { g_=g; }
  
  // Getters - Metodi di accesso
  virtual Velocity v0() const { return v0_; }
  virtual double beta() const { return beta_; }
  virtual double m() const { return m_; }
  virtual double g() const { return g_; }

  virtual vector<Velocity> velocity(double tmin, double tmax) const = 0;

private:
  Velocity v0_;
  double beta_;
  double m_;
  double g_;
};
#endif
