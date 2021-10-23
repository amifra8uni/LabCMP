/*Complex.h
  Archivio di intestazione (o header file) della classe Complex*/

class Complex {
 public:
  // constructors o costruttori
  Complex ();
  Complex(double real, double imag);
  Complex(const Complex& complex);

  //getters o funzioni d'accesso
  double real();
  double imag();

  //setters o funzioni d'attualizzamento
  void setReal(double real);
  void setImag(double imag);

  void print();

 private:
  double real_; 
  double imag_;
};
