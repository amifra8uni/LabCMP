// Atmosphere.h

#ifndef Atmosphere_h
#define Atmosphere_h

class Atmosphere {
 public:

// Costrutttori
  Atmosphere(); // Predefinito}
  Atmosphere(double A, double C_d, double F107, double A_p); // Predefinito
  Atmosphere(const Atmosphere& atm); // Copia

// Distruttore
  ~Atmosphere();

// Metodi di accesso - Getter Methods
  double A() const;
  double C_d() const;
  double F107() const;
  double A_p() const;

// Metodi di aggiornamento - Setter Methods
  void setA(double A);
  void setC_d(double C_d);
  void setF107(double F107);
  void setA_p(double A_p);

// Memeber functions
  double T(); // Temperatura

  double mu(double h); // molecular mass of the air
  double rho(double h);// density of the air
  // Drag force: dal momento che è parallelo alla velocità, lo tratto come uno scalare
  double D(double v, double h);

 private:
  double A_;
  double C_d_;
  double F107_;
  double A_p_;

};
#endif
