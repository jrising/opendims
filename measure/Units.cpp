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
Unit Units::hr = Unit("hr", Dims::time(), &Units::s, 3600);
Unit Units::yr = Unit("yr", Dims::time());
Unit Units::m = Unit("m", Dims::distance());
Unit Units::ha = Unit("ha", Dims::distance() * Dims::distance());
Unit Units::kg = Unit("kg", Dims::mass());
Unit Units::mt = Unit("mt", Dims::mass(), &Units::kg, 1000);
Unit Units::deg = Unit("deg", Dims::angle());
