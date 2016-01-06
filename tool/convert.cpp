#include <iostream>
#include "parse.h"

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

  Quantity source = readCompoundExpression(expression);
  Unit target = readCompoundExpression(units).getUnit();

  Quantity result = convertQuantity(source, target);
  cout << result << endl;

  return 0;
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

