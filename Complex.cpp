/*Complex.cpp
  Archivio per vedere se funziona la classe Complex*/

#include "Complex.h"

int main() {

  Complex c1(3,4);
  c1.print();

  c1.setReal(6);
  c1.setImag(8);
  c1.print();

  return 0;
}
