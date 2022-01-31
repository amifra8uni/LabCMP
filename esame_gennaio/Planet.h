/* Planet.h
   Archivio di intestazione (header) della classe Particle */

#ifndef Planet_h
#define Planet_h

class Planet {
 public:
  // Costrutttori
  Planet(); // Predefinito
  Planet(double radius, double mass, double grav); // Regolare
  Planet(const Planet& planet);// Copia

  // Distruttore
  ~Planet();

// Metodi di accesso - Getter Methods
  double R() const;
  double M() const;
  double G() const;


// Metodi di aggiornamento - Setter Methods
  void setR(double R);
  void setM(double M);
  void setG(double G);

  // Metodi accessori - utility methos
  void print() const;

 private:
  // Data members
  double R_;
  double M_;
  double G_;

};
#endif
