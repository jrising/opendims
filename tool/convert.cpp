#include <iostream>
#include <string>
#include <regex>
#include <dims/Dims.h>
#include <measure/Inds.h>
#include <measure/Units.h>
#include <measure/Measure.h>

using namespace std;
using namespace openworld;

string getIndicator(string& expression);
Indicator readIndicator(string units);
Measure readExpression(string expression);

int main(int argc, const char* argv[])
{
  // Output the units of an expression given on the command-line
  if (argc < 2) {
    cout << "Call with an expression to determine the units of." << endl;
    return -1;
  }

  string expression = argv[1];
  if (argc > 2) {
    for (unsigned ii = 2; ii < argc; ii++)
      expression += argv[ii];
  }

  cout << readExpression(expression) << endl;
  return 0;
}

string getIndicator(string& expression) {
  smatch match;
  if (regex_match(expression, match, regex("\\s*\\[([^\\]]+)\\]"))) {
    expression = expression.substr(match[0].length());
    return match[1];
  }

  return "";
}

Indicator readIndicator(string units) {
  if (Indicator* ind = Inds::get(units))
    return *ind;

  if (Unit* unit = Units::get(units))
    return LinearIndicator("", *unit, 0, 0);

  if (Dimensions* dims = GlobalDimensions::tryget(units))
    return LinearIndicator("", Unit("", *dims), 0, 0);

  throw invalid_argument("Unknown dimensions: " + units);
}

Measure readExpression(string expression) {
  string units = getIndicator(expression);
  if (units != "") {
    Indicator ind = readIndicator(units);
    return Measure(1, ind);
  } else {
    cout << "Only units are supported: expression must match '[...]'." << endl;
    /*string value = getValue(expression);
      if (value) {
      double readValue(value);
      string valueunits = getIndicator(expression);
      if (valueunits)
      cout << Measure(value, readIndicator(valueunits));

      cout << readMeasure(expression) << endl;*/
  }

  throw invalid_argument("Unknown expression: " + expression);
}
