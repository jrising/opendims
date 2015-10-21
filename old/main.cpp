/* A simple test of the Measure classes */

#include <iostream.h>
#include "measure.h"

void main() {
  Measure mass1(kg), mass2(kg);
  Measure distance1(m), distance2(m);
  Measure totalmoment(kg * Sqr(m));

  mass1 = 1.0 * kg;
  mass2 = 2.0 * kg;
  distance1 = 3.0 * m;
  distance2 = 2.0 * m;

  totalmoment = mass1 * Sqr(distance1) + mass2 * Sqr(distance2);
  cout << totalmoment << endl;  // 17.0 kg m^2;

  totalmoment = mass1 * Sqr(distance1) + mass2 * distance2; // error
  cout << totalmoment << endl;
}
