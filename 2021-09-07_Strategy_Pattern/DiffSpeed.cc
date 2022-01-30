#include "DiffSpeed.h"
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

DiffSpeed::DiffSpeed(const std::string& name, double beta, double m) : Function(name) {
  beta_ = beta;
  m_ = m;
}

double DiffSpeed::value(double x) const {
  return beta_*x/m_;
}

void DiffSpeed::print() const {
  cout << "Differenziale della velocità con nome: " << name()
       << " beta: " << beta_
       << " massa: " << m_
       << endl;
}
