/* Materiale.h
   Archivio di intestazione (header) della classe Material */

#include "Particella.h"
#include "TRandom3.h"

class Materiale {

 public:

  // Costrutttori
  Materiale();                                                                     // Predefinito
  Materiale(double density, double atomicMass, double atomicNumber, double ionisation, double lung_rad, double delta, double e_critica);  // Regolare
  Materiale(const Materiale& material);                                             // Copia

  // Distruttore
  ~Materiale();

  // Metodi di accesso - Getter Methods
  double rho() const;
  double A() const;
  double Z() const;
  double I() const;
  double X_0() const;
  double delta() const;
  double E_c() const;

  // Metodi di aggiornamento - Setter Methods
  void setRho(double rho);
  void setA(double A);
  void setZ(double Z);
  void setI(double I);
  void setX_0(double X_0);
  void setDelta(double delta);
  void setE_c(double E_c);

  // Memeber functions
  double dE(Particella& particle, double dx, double res, TRandom*   gen);
  double prob_Brems(double dx);

  // Info
  void print() const;
  
 private:

  // Data members
  double rho_;
  double A_;
  double Z_;
  double I_;
  double X_0_;
  double delta_;
  double E_c_;
};
