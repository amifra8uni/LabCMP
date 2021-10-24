/*Complex.h
  Archivio d'intestazione (o header file) della classe Complex*/

class Complex {
 public:

  //Costruttori - constructor
  Complex ();                      // Predefinito - Default
  Complex(const Complex& complex); // Copia - Copy
  //Named Constructor Idiom
  static Complex Polari(double r,double theta);
  static Complex Cartesiane(double real, double imag);

  //getters o funzioni d'accesso
  double real();
  double imag();

  //setters o funzioni d'aggiornamento
  void setReal(double real);
  void setImag(double imag);

  //Overload operators
  Complex operator+(const Complex& rhs) const;
  Complex operator-(const Complex& rhs) const;
  Complex operator*(const Complex& rhs) const;
  Complex operator/(const Complex& rhs) const;
  Complex operator+(const double&  rhs) const;
  Complex operator-(const double&  rhs) const;
  Complex operator*(const double&  rhs) const;
  Complex operator/(const double&  rhs) const;
  
  //Utility functions
  void print();
  void re();
  void im();
  void r();
  void phi();
  void mag();
  void phase();

 private:
  double real_; // data member 
  double imag_; // data member
  
  //Costruttore regolare - regular constructor
  Complex(double real, double imag) {
    real_ = real;
    imag_ = imag;
  };
};

