#include <iostream>
#include "parse.h"

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
