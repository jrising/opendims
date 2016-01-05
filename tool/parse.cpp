#include <iostream>
#include <string>
#include <regex>
#include <dims/Dims.h>
#include <measure/Inds.h>
#include <measure/Units.h>
#include <measure/Quantity.h>

using namespace std;
using namespace openworld;

Unit readUnit(string units);
bool isValue(string expression);
double readValue(string& expression);
Quantity readCompoundExpression(string expression);
Quantity readSimpleExpression(string expression);

/*
 * EXP = NUM | DIM | EXP EXP | EXP_OP_EXP
 * DIM = UNIT | UNIT_^_NUM
 * OP = * | /
 */

int main(int argc, const char* argv[])
{
  // Output the units of an expression given on the command-line
  if (argc < 2) {
    cout << "Call with an expression to parse." << endl;
    return -1;
  }

  string expression = argv[1];
  for (int ii = 2; ii < argc; ii++) {
    expression += " ";
    expression += argv[ii];
  }

  Quantity source = readCompoundExpression(expression);
  cout << source << endl;

  return 0;
}

Quantity readCompoundExpression(string expression) {
  cout << expression << endl;

  if (expression.find("/") != string::npos) {
    if (count(expression.begin(), expression.end(), '/') > 1)
      throw invalid_argument("Only 1 division allowed.");

    string numer = expression.substr(0, expression.find_first_of('/'));
    string denom = expression.substr(expression.find_first_of('/') + 1);

    Quantity numerquant = readCompoundExpression(numer);
    Quantity denomquant = readCompoundExpression(denom);

    return numerquant / denomquant;
  }

  // Clean up expression
  expression = regex_replace(expression, (regex) "[*]", (string) " "); // * is superfluous
  expression = regex_replace(expression, (regex) "\\s*[\\^]\\s*", (string) "^"); // logic cleaner if don't allow _^_.

  Quantity result = Quantity(1., Units::none);
  istringstream expstr(expression);
  string token;
  while (getline(expstr, token, ' ')) {
    if (token.size() == 0)
      continue;
    result.overwrite(result * readSimpleExpression(token));
  }

  return result;
}

Quantity readSimpleExpression(string expression) {
  cout << expression << endl;

  if (isValue(expression)) {
    double value = readValue(expression);
    return Quantity(value, Units::none);
  }

  if (expression.find("^") != string::npos) {
    string base = expression.substr(0, expression.find_first_of('^'));
    string power = expression.substr(expression.find_first_of('^') + 1);

    Unit unit = readUnit(base);
    return Quantity(1., unit.raisedTo(readValue(power)));
  }

  Unit unit = readUnit(expression);
  return Quantity(1., unit);
}

Unit readUnit(string units) {
  if (Inds::get(units))
    throw invalid_argument("Cannot handle indicator: " + units);

  if (Unit* unit = Units::get(units))
    return *unit;

  if (Dimensions* dims = GlobalDimensions::tryget(units))
    return Unit("", *dims);

  throw invalid_argument("Unknown units: " + units);
}

bool isValue(string expression) {
  return regex_match(expression, regex("^\\s*[0-9]*\\.?[0-9]*(e[0-9]+)?"));
}

double readValue(string& expression) {
  smatch match;
  if (regex_search(expression, match, regex("^\\s*[0-9]*\\.?[0-9]*(e[0-9]+)?"))) {
    double value = stod(match[0]);
    expression = expression.substr(match[0].length());
    return value;
  }

  throw invalid_argument("No value beginning: " + expression);
}
