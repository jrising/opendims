/******************************************************************************\
 * Units: standard units
 ******************************************************************************
 *
\******************************************************************************/

#include "Units.h"

using namespace openworld;

Unit Units::none = Unit("none", Dims::none());
Unit Units::individuals = Unit("individuals", Dims::individuals());

Unit Units::s = Unit("s", Dims::time());
Unit Units::min = Unit("min", Dims::time(), &Units::s, 60);
Unit Units::hr = Unit("hr", Dims::time(), &Units::s, 3600);
Unit Units::day = Unit("hr", Dims::time(), &Units::s, 24*3600);
Unit Units::yr = Unit("yr", Dims::time());

Unit Units::m = Unit("m", Dims::distance());
Unit Units::cm = Unit("cm", Dims::distance(), &Units::m, .01);
Unit Units::mm = Unit("mm", Dims::distance(), &Units::m, .001);
Unit Units::km = Unit("km", Dims::distance(), &Units::m, 1000);
Unit Units::inch = Unit("inch", Dims::distance(), &Units::m, .01*2.54);
Unit Units::ft = Unit("ft", Dims::distance(), &Units::m, .01*2.54*12);
Unit Units::mi = Unit("mi", Dims::distance(), &Units::m, .01*2.54*12*5280);

Unit Units::ha = Unit("ha", Dims::distance() * Dims::distance());

Unit Units::kg = Unit("kg", Dims::mass());
Unit Units::mt = Unit("mt", Dims::mass(), &Units::kg, 1000);

Unit Units::deg = Unit("deg", Dims::angle());
Unit Units::rad = Unit("rad", Dims::angle(), &Units::deg, 180.0 / M_PI);
