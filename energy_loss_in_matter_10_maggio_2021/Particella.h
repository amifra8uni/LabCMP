/* Particella.h
   Archivio di intestazione (header) della classe Particle */

class Particella {

 public:

  // Costrutttori
  Particella(); // Predefinito
  Particella(double mass, double charge, double energy); // Regolare
  Particella(const Particella& particle); // Copia

  // Distruttore
  ~Particella();

  // Metodi di accesso - Getter Methods
  double m() const;
  double q() const;
  double E() const;

  // Metodi di aggiornamento - Setter Methods
  void setM(double m);
  void setQ(double q);
  void setE(double E);

  // Memeber functions
  double K();
  double beta();
  double gamma();
  double betagamma();

  // Info
  void print() const;

 private:

  // Data members
  double m_;
  double q_;
  double E_;
};
