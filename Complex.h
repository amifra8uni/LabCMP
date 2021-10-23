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

  /*Named Constructor Idiom
  static Complex Polar(double r,double theta);
  static Complex Cartesian(double x, double y);*/

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
  double real_; 
  double imag_;
  
};
