/*Complex.h
  Archivio di intestazione (o header file) della classe Complex*/

class Complex {
 public:
  Complex ();                      //costruttore predefinito - Default constructor
  Complex(const Complex& complex); //costruttore copia - Copy constructor
  
  //getters o funzioni d'accesso
  double real();
  double imag();

  //setters o funzioni d'aggiornamento
  void setReal(double real);
  void setImag(double imag);

  //Named Constructor Idiom
  static Complex Polari(double r,double theta);
  static Complex Cartesiane(double real, double imag);

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

