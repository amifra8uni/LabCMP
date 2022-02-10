#ifndef TwoBodyDecay_h
#define TwoBodyDecay_h

//Archivio di intestazione di ROOT: numeri casuali, grafici, salvataggio
#include "TLorentzVector.h"
#include "TRandom3.h"

class TwoBodyDecay {
 public:

  // Costruttori
  TwoBodyDecay(TLorentzVector mamma, double tau, double m1, double m2) {
    mom_ = mamma;
    tau_ = tau; // s
    m1_ = m1;   // GeV
    m2_ = m2;   // GeV
  };

  // Distruttori
  ~TwoBodyDecay() {};

  // Metodi di aggiornamento - Setter methods
  void setMom(TLorentzVector mom) {mom_ = mom;};
  //void setP2(double p) {son2_.setP = p}

  // Metodi di accesso - Getter Mathods
  TLorentzVector getSon1() const { return son1_; };
  TLorentzVector getSon2() const { return son2_; };
  
  // Metodo per il boost
  void decay(TRandom* gen) {
    double m1 = m1_;
    double m2 = m2_;
    double p_cdm = sqrt( mom_.M()*mom_.M()*mom_.M()*mom_.M() + m1*m1*m1*m1 + m2*m2*m2*m2 - 2*mom_.M()*mom_.M()*m1*m1 - 2*mom_.M()*mom_.M()*m2*m2 ) / (2*mom_.M()); // GeV
    // Genero un vettore uniformemente distribuito sulla superficie di una sfera unitaria
    double x, y, z;
    gen->Sphere(x, y, z, 1);
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    // CdM
    son1_.SetPxPyPzE( p_cdm*x,  p_cdm*y,  p_cdm*z, sqrt(m1*m1 + p_cdm*p_cdm));
    son2_.SetPxPyPzE( -p_cdm*x, -p_cdm*y, -p_cdm*z, sqrt(m2*m2   + p_cdm*p_cdm));
  };

  void boost() {
    // Trasformazion (boost) nel sistema di laboratorio
    // Lab
    son1_.Boost(mom_.BoostVector());
    son2_.Boost(mom_.BoostVector());
  };

  double distance_decay(TRandom* gen) {
    double c = 299792458.; // m/s
    return gen->Exp(mom_.Beta()*mom_.Gamma()*c*tau_);
  };
  
  private:
  // Data members
    TLorentzVector mom_;
    TLorentzVector son1_;
    TLorentzVector son2_;
    double tau_;
    double m1_;
    double m2_;
  };
#endif 
