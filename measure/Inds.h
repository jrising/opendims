#ifndef INDS_H
#define INDS_H

#include "Indicator.h"

using namespace std;

namespace openworld {
  class Inds {
  public:
    static Indicator none;

    static LinearIndicator lat;
    static LinearIndicator lon;

    static LinearIndicator unixtime;

    static LinearIndicator ce;
    static LinearIndicator bce;

    static LinearIndicator kelvin;
    static LinearIndicator celsius;
    static LinearIndicator fahrenheit;

    static Indicator* get(string name) {
      if (name == "lat")
        return &lat;
      if (name == "lon")
        return &lon;

      if (name == "unixtime")
        return &unixtime;

      if (name == "B.C.E.")
        return &bce;
      if (name == "C.E.")
        return &ce;

      if (name == "K")
        return &kelvin;
      if (name == "C")
        return &celsius;
      if (name == "F")
        return &fahrenheit;

      return NULL;
    }
  };
}

#endif
