/******************************************************************************\
 * Inds: standard indicators
 ******************************************************************************
 *
\******************************************************************************/

#include "Inds.h"
#include <limits>
#include <stdexcept>
#include "Indicator.h"
#include "Units.h"

using namespace openworld;

Indicator Inds::none = LinearIndicator("", Units::none, 0, numeric_limits<double>::max());

LinearIndicator Inds::lat = LinearIndicator("latitude", Units::deg, -90, 90);
LinearIndicator Inds::lon = LinearIndicator("longitude", Units::deg, -180, 180);

LinearIndicator Inds::unixtime = LinearIndicator("Unixtime", Units::s, 0, numeric_limits<double>::max());

LinearIndicator Inds::ce = LinearIndicator("C.E.", Units::yr, 1, numeric_limits<double>::max());
LinearIndicator Inds::bce = LinearIndicator("B.C.E.", Units::bceyr, 1, numeric_limits<double>::max(), &Inds::ce, 1);

LinearIndicator Inds::kelvin = LinearIndicator("K", Units::degC, numeric_limits<double>::min(), numeric_limits<double>::max());
LinearIndicator Inds::celsius = LinearIndicator("C", Units::degC, numeric_limits<double>::min(), numeric_limits<double>::max(), &Inds::kelvin, -273.15);
LinearIndicator Inds::fahrenheit = LinearIndicator("F", Units::degF, numeric_limits<double>::min(), numeric_limits<double>::max(), &Inds::kelvin, -273.15 * 1.8 + 32);

