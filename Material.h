/* Material.h
   Archivio di intestazione (header) della classe Material */

#include "Particle.h"

class Material {

 public:

  // Costrutttori
  Material(); // Predefinito
  Material(double density, double atomicMass, double charge, double ionisation);  // Regolare
  Material(const Material& material); // Copia

  // Distruttore
  ~Material();

  // Metodi di accesso - Getter Methods
  double rho() const;
  double A() const;
  double Z() const;
  double I() const;

  // Metodi di aggiornamento - Setter Methods
  void setRho(double rho);
  void setA(double A);
  void setZ(double Z);
  void setI(double I);

  // Memeber functions
  double dEdx(Particle& particle, double delta);

 private:

  // Data members
  double rho_;
  double A_;
  double Z_;
  double I_;
};
