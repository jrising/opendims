#ifndef INDS_H
#define INDS_H

#include "Indicator.h"

using namespace std;

namespace openworld {
  class Inds {
  public:
    static Indicator lat;
    static Indicator lon;

    static Indicator unixtime;

    static Indicator* get(string name) {
      if (name == "lat")
        return &lat;
      if (name == "lon")
        return &lon;
      if (name == "unixtime")
        return &unixtime;

      return NULL;
    }
  };
}

#endif
