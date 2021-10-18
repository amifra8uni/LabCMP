//test
//
# include <iostream>
using namespace std;

class Complex{
  
private:
  double real,imag;

public:
  Complex(){
    real=0;
    imag=0;
  }

  Complex(double r, double i){
    real=r;
    imag=i;
  }
  
  Complex(Complex &obj){
    real=obj.real;
    imag=obj.imag;
  }

  Complex add(Complex c){
    Complex Add;
    Add.real=real+c.real;
    Add.imag=imag+c.imag;
    return Add;
  }

  Complex sub(Complex c){
    Complex Sub;
    Sub.real=real-c.real;
    Sub.imag=imag-c.imag;
    return Sub;
  }

  Complex mult(Complex c){
    Complex Mult;
    Mult.real=real*c.real-imag*c.imag;
    Mult.imag=real*c.imag-imag*c.real;
    return Mult;
  }

  Complex div(Complex c){
    Complex Div;
    Div.real=(real*c.real+imag*c.imag)/(c.real*c.real+c.imag*c.imag);
    return Div;
  }

  void print(){
    cout<<real<<"+"<imag<<"i"<<endl<<endl;
  }

  double re() const{
    return real;
  }

  double im() const{
    return im;
  }


















      

  
