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
double getValue(string& expression);
Measure readExpression(string expression);
ostream& displayGeneral(ostream& out, Measure measure, bool showValue);

int main(int argc, const char* argv[])
{
  // Output the units of an expression given on the command-line
  if (argc < 2) {
    cout << "Call with an expression to determine units; follow with unit to convert." << endl;
    return -1;
  }

  string expression = argv[1];
  int nextargc = 2;
  if (argc > 2 && expression.find("[") == string::npos) {
    expression += " ";
    expression += argv[nextargc++];
  }

  Measure source = readExpression(expression);

  if (argc > nextargc) {
    Measure target = readExpression(argv[nextargc++]);
    displayGeneral(cout, source, true) << " to ";
    displayGeneral(cout, target, false) << endl;
  } else
    displayGeneral(cout, source, true) << endl;

  return 0;
}

string getIndicator(string& expression) {
  smatch match;
  if (regex_search(expression, match, regex("^\\s*\\[([^\\]]+)\\]"))) {
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

double getValue(string& expression) {
  smatch match;
  if (regex_search(expression, match, regex("^\\s*[0-9]*\\.?[0-9]*(e[0-9]+)?"))) {
    double value = stod(match[0]);
    expression = expression.substr(match[0].length());
    return value;
  }

  throw invalid_argument("No value beginning: " + expression);
}

Measure readExpression(string expression) {
  string units = getIndicator(expression);
  if (units != "") {
    Indicator ind = readIndicator(units);
    return Measure(1, ind);
  } else {
    double value = getValue(expression);
    string valueunits = getIndicator(expression);
    if (valueunits != "")
      return Measure(value, readIndicator(valueunits));
    else
      throw invalid_argument("Expression without dimensions: " + expression);
  }

  throw invalid_argument("Unknown expression: " + expression);
}

ostream& displayGeneral(ostream& out, Measure measure, bool showValue) {
  // Check if this is a quantity
  if (measure.getIndicator().getName() == "") {
    if (showValue)
      out << Quantity(measure.getValue(), measure.getIndicator().getUnit());
    else
      out << measure.getIndicator().getUnit();
  } else {
    if (showValue)
      out << measure;
    else
      out << measure.getIndicator();
  }

  return out;
}
