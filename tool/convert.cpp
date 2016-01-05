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
bool isValue(const char* expression);
double getValue(string& expression);
Measure readExpression(string expression);
ostream& displayGeneralMeasure(ostream& out, Measure measure, bool showValue);
ostream& displayGeneralIndicator(ostream& out, Indicator indicator);
Measure convertMeasure(Measure measure, Indicator& indicator);
Quantity convertQuantity(Quantity quantity, const Unit& unit);
ostream& displayConvert(ostream& out, Measure measure, Indicator& indicator);

int main(int argc, const char* argv[])
{
  // Output the units of an expression given on the command-line
  if (argc < 3) {
    cout << "Call with an expression to determine units; follow with unit to convert." << endl;
    return -1;
  }

  if (isValue(argv[1])) {
    string expression = argv[1];
    expression += " ";
    expression += argv[2];

    Measure source = readExpression(expression);

    if (argc == 3)
      displayGeneralMeasure(cout, source, true) << endl;
    else {
      string targetindicator = string(argv[3]);
      Indicator target = readIndicator(getIndicator(targetindicator));

      displayGeneralMeasure(cout, source, true) << " to ";
      displayGeneralIndicator(cout, target) << endl;

      displayConvert(cout, source, target) << endl;
    }
  } else {
    Measure source = readExpression(argv[1]);
    string targetindicator = string(argv[2]);
    Indicator target = readIndicator(getIndicator(targetindicator));

    displayGeneralMeasure(cout, source, true) << " to ";
    displayGeneralIndicator(cout, target) << endl;

    displayConvert(cout, source, target) << endl;
  }

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

  if (Unit* unit = Units::get(units)) {
    cout << "Got a " << typeid(*unit).name() << endl;
    return LinearIndicator("", *unit, 0, 0);
  }

  if (Dimensions* dims = GlobalDimensions::tryget(units))
    return LinearIndicator("", Unit("", *dims), 0, 0);

  throw invalid_argument("Unknown dimensions: " + units);
}

bool isValue(const char* expression) {
  return regex_match(expression, regex("^\\s*[0-9]*\\.?[0-9]*(e[0-9]+)?"));
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

ostream& displayGeneralMeasure(ostream& out, Measure measure, bool showValue) {
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

ostream& displayGeneralIndicator(ostream& out, Indicator indicator) {
  // Check if this is a quantity
  if (indicator.getName() == "") {
    out << indicator.getUnit();
  } else {
    out << indicator;
  }

  return out;
}

Measure convertMeasure(Measure measure, Indicator& indicator) {
  // Check that dimensions match
  if (measure.getIndicator().getUnit().getDimensions() != indicator.getUnit().getDimensions())
    throw invalid_argument("Dimensions do not match!");

  // Convert the units
  const Indicator& sourceIndicator = measure.getIndicator();
  Indicator& targetIndicator = indicator;
  if (sourceIndicator.isConvertible() && targetIndicator.isConvertible()) {
    if (sourceIndicator.getStandardUnit() != targetIndicator.getStandardUnit())
      throw invalid_argument("Units are not commesurate!");

    double standardValue = sourceIndicator.convertToStandardIndicator(measure.getValue());
    double targetValue = targetIndicator.convertFromStandardIndicator(standardValue);
    return Measure(targetValue, indicator);
  } else if (!sourceIndicator.isConvertible())
    throw invalid_argument("Source indicator is not convertible.");
  else if (!targetIndicator.isConvertible())
    throw invalid_argument("Target indicator is not convertible.");
  else
    throw invalid_argument("Indicators are not convertible.");
}

Quantity convertQuantity(Quantity quantity, const Unit& unit) {
  // Check that dimensions match
  if (quantity.getUnit().getDimensions() != unit.getDimensions())
    throw invalid_argument("Dimensions do not match!");

  // Convert the units
  const Unit& sourceUnit = quantity.getUnit();
  const Unit& targetUnit = unit;
  cout << sourceUnit << ", " << typeid(unit).name() << endl;

  if (sourceUnit.getStandardUnit() != targetUnit.getStandardUnit())
    throw invalid_argument("Units are not commesurate!");

  double standardValue = sourceUnit.convertToStandardUnits(quantity.getValue());
  double targetValue = targetUnit.convertFromStandardUnits(standardValue);
  return Quantity(targetValue, unit);
}

ostream& displayConvert(ostream& out, Measure measure, Indicator& indicator) {
  if (measure.getIndicator().getName() != "" && indicator.getName() != "")
    return cout << convertMeasure(measure, indicator);
  else if (measure.getIndicator().getName() == "" && indicator.getName() != "")
    throw invalid_argument("Cannot convert a quantity to an indicator.");
  else if (measure.getIndicator().getName() != "" && indicator.getName() == "")
    throw invalid_argument("Need an indicator to convert a measure.");
  else {
    Quantity quantity = Quantity(measure.getValue(), measure.getIndicator().getUnit());
    Quantity result = convertQuantity(quantity, indicator.getUnit());
    return out << result;
  }
}

