#include <iostream>
#include "parse.h"
#include <measure/Measure.h>

Measure readMeasureExpression(string expression);
Indicator& readIndicator(string units);
Measure convertMeasure(Measure& measure, Indicator& indicator);
Quantity convertQuantity(Quantity quantity, const Unit& unit);

int main(int argc, const char* argv[])
{
  // Output the units of an expression given on the command-line
  if (argc < 3) {
    cout << "Call with both the current and target units." << endl;
    return -1;
  }

  string expression = argv[1];
  for (int ii = 2; ii < argc - 1; ii++) {
    expression += " ";
    expression += argv[ii];
  }

  string units = argv[argc-1];

  bool pointOfNoReturn = false;
  try {
    Measure source = readMeasureExpression(expression);
    pointOfNoReturn = true;
    Indicator& target = readIndicator(units);

    Measure result = convertMeasure(source, target);
    cout << result << endl;
  } catch (invalid_argument ex) {
    if (pointOfNoReturn)
      throw ex;

    Quantity source = readCompoundExpression(expression);
    Unit target = readCompoundExpression(units).getUnit();

    Quantity result = convertQuantity(source, target);
    cout << result << endl;
    return 0;
  }

  return 0;
}

Indicator& readIndicator(string units) {
  if (Indicator* ind = Inds::get(units))
    return *ind;

  throw invalid_argument("Unknown indicator: " + units);
}

Measure readMeasureExpression(string expression) {
  if (expression.find(" ") != string::npos) {
    string value = expression.substr(0, expression.find_first_of(' '));
    string units = expression.substr(expression.find_first_of(' ') + 1);

    return Measure(readValue(value), readIndicator(units));
  }

  return Measure(1, readIndicator(expression));
}

Quantity convertQuantity(Quantity quantity, const Unit& unit) {
  // Check that dimensions match
  if (quantity.getUnit().getDimensions() != unit.getDimensions())
    throw invalid_argument("Dimensions do not match!");

  // Convert the units
  const Unit& sourceUnit = quantity.getUnit();
  const Unit& targetUnit = unit;

  if (sourceUnit.getStandardUnit() != targetUnit.getStandardUnit())
    throw invalid_argument("Units are not commesurate!");

  double standardValue = sourceUnit.convertToStandardUnits(quantity.getValue());
  double targetValue = targetUnit.convertFromStandardUnits(standardValue);
  return Quantity(targetValue, unit);
}

Measure convertMeasure(Measure& measure, Indicator& indicator) {
  // Check that dimensions match
  if (measure.getIndicator().getUnit().getDimensions() != indicator.getUnit().getDimensions())
    throw invalid_argument("Dimensions do not match!");

  // Convert the units
  const Indicator& sourceIndicator = measure.getIndicator();
  Indicator& targetIndicator = indicator;
  if (sourceIndicator.getStandardIndicator() != targetIndicator.getStandardIndicator())
    throw invalid_argument("Indicators are not commesurate!");

  double standardValue = sourceIndicator.convertToStandardIndicator(measure.getValue());
  double targetValue = targetIndicator.convertFromStandardIndicator(standardValue);
  return Measure(targetValue, indicator);
}

