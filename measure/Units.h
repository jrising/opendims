#ifndef UNITS_H
#define UNITS_H

#include <math.h>
#include "Unit.h"

namespace openworld {
  class Units {
  public:
    static Unit none;
    static Unit individuals;

    static Unit s;
    static Unit min;
    static Unit hr;
    static Unit day;
    static Unit yr; // can't convert htis yet!
    //static Unit month = GlobalUnit::add("month", Depends(theDate, day*365.25/12));
    //static Unit year = GlobalUnit::add("year", Depends(theDate, day*365.25));*/

    // space variables
    static Unit m;
    static Unit cm;
    static Unit mm;
    static Unit km;
    static Unit inch;
    static Unit ft;
    static Unit mi;

    static Unit ha;

    // mass variables
    static Unit kg;
    static Unit mt;

    // angles
    static Unit deg;
    static Unit rad;

    static Unit* get(string name) {
      if (name == "none")
        return &none;
      if (name == "individuals")
        return &individuals;

      if (name == "s")
        return &s;
      if (name == "min")
        return &min;
      if (name == "hr")
        return &hr;
      if (name == "day")
        return &day;
      if (name == "yr")
        return &yr;

      if (name == "m")
        return &m;
      if (name == "cm")
        return &cm;
      if (name == "mm")
        return &mm;
      if (name == "km")
        return &km;
      if (name == "inch")
        return &inch;
      if (name == "ft")
        return &ft;
      if (name == "mi")
        return &mi;

      if (name == "ha")
        return &ha;

      if (name == "kg")
        return &kg;
      if (name == "mt")
        return &mt;

      if (name == "deg")
        return &deg;
      if (name == "rad")
        return &rad;

      return NULL;
    }
  };
}

#endif
