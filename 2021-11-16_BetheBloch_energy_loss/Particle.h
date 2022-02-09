/* Particle.h
   Archivio di intestazione (header) della classe Particle */

#ifndef Particle_h
#define Particle_h

class Particle {

 public:

  // Costrutttori
  Particle(); // Predefinito
  Particle(double mass, double charge, double threemomentum); // Regolare
  Particle(const Particle& particle); // Copia

  // Distruttore
  ~Particle();

  // Metodi di accesso - Getter Methods
  double m() const;
  double q() const;
  double p() const;

  // Metodi di aggiornamento - Setter Methods
  void setM(double m);
  void setQ(double q);
  void setP(double p);

  // Memeber functions
  double beta();
  double gamma();
  double betagamma();
  double E();

 private:

  // Data members
  double m_;
  double q_;
  double p_;
};
#endif
