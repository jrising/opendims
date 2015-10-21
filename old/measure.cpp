// measure.cpp - Function definitions from mechanical measures classes

#include <stdlib.h>
#include <math.h>
#include "measure.h"

/* ----- Accessory struction Functions ----- */

Dimensions::Dimensions(float ndist, float ntime, float nmass) {
  dist = ndist;
  time = ntime;
  mass = nmass;
}

bool Dimensions::operator==(const Dimensions &right) const {
  return (dist == right.dist && time == right.time && mass == right.mass);
}

/* ----- Top level functions ----- */

// Initialization

Measure::Measure(const Measure &units) :
  factors(units.factors) {
  value = units.value;
}

Measure::Measure(double nconst) :
  factors(0, 0, 0) {
  value = nconst;
}

Measure::Measure(Dimensions nfactors) :
  factors(nfactors) {
  value = 0;
}

const Measure &Measure::operator=(const Measure &nvalue) {
  if (factors == nvalue.factors) {
    value = nvalue();
    return nvalue;
  } else
    dimerror("defining");
}

// Evalution

double Measure::operator()(const Measure &convert) const {
  if (!(factors == convert.factors))
    dimerror("measure eval-convert");
  return ((*this) * 1.0 / convert)();
}

double Measure::operator()() const {
  return value;
}

// Operators

const Measure Measure::operator+(const Measure &right) const {
  if (factors == right.factors) {
    Measure addresult(*this);
    addresult.value = value + right();
    return addresult;
  } else
    dimerror("measure addition");
}

const Measure Measure::operator-(const Measure &right) const {
  if (factors == right.factors) {
    Measure subresult(*this);
    subresult.value = value - right();
    return subresult;
  } else
    dimerror("measure subtraction");
}

const Measure Measure::operator*(const Measure &right) const {
  Measure mulresult(Dimensions(factors.dist + right.factors.dist,
			       factors.time + right.factors.time,
			       factors.mass + right.factors.mass));
  mulresult.value = value * right();
  return mulresult;
}

const Measure Measure::operator*(double right) const {
  Measure mulresult(factors);
  mulresult.value = value * right;
  return mulresult;
}

const Measure operator*(double left, const Measure &right) {
  Measure mulresult(right.factors);
  mulresult.value = left * right.value;
  return mulresult;
}

const Measure Measure::operator/(const Measure &right) const {
  Measure divresult(Dimensions(factors.dist - right.factors.dist,
			       factors.time - right.factors.time,
			       factors.mass - right.factors.mass));
  divresult.value = value / right();
  return divresult;
}

const Measure Measure::operator/(double right) const {
  Measure divresult(factors);
  divresult.value = value / right;
  return divresult;
}

const Measure operator/(double left, const Measure &right) {
  Measure divresult(Dimensions(-right.factors.dist, -right.factors.time,
			       -right.factors.mass));
  divresult.value = left / right.value;
  return divresult;
}

const Measure Measure::operator-() const {
  Measure mnsresult(factors);
  mnsresult.value = -value;
  return mnsresult;
}

const Measure Measure::operator+=(const Measure &right) {
  return *this = *this + right;
}

const Measure Measure::operator-=(const Measure &right) {
  return *this = *this - right;
}

// Math Functions

const Measure Sqr(const Measure &base) {
  Measure sqrresult(Dimensions(2.0 * base.factors.dist,
			       2.0 * base.factors.time,
			       2.0 * base.factors.mass));
  sqrresult.value = base.value * base.value;
  return sqrresult;
}

const Measure Sqrt(const Measure &base) {
  Measure sqrtresult(Dimensions(.5 * base.factors.dist,
				.5 * base.factors.time,
				.5 * base.factors.mass));
  sqrtresult.value = sqrt(base.value);
  return sqrtresult;
}

const Measure Pow(const Measure &base, const Measure &power) {
  if (!(k.factors == power.factors))
    dimerror("exponentiation");

  Measure powresult(Dimensions(base.factors.dist * power(),
			       base.factors.time * power(),
			       base.factors.mass * power()));

  powresult.value = pow(base.value, power.value);
  return powresult;
}

// Relational functions

bool Measure::operator<(const Measure &right) const {
  if (!(factors == right.factors))
    dimerror("< comparison");

  return (value < right.value);
}

bool Measure::operator>(const Measure &right) const {
  if (!(factors == right.factors))
    dimerror("> comparison");

  return (value > right.value);
}

bool Measure::operator==(const Measure &right) const {
  if (!(factors == right.factors))
    dimerror("== comparison");

  return (value == right.value);
}

bool Measure::operator<=(const Measure &right) const {
  return (*this < right || *this == right);
}

bool Measure::operator>=(const Measure &right) const {
  return (*this > right || *this == right);
}

bool Measure::operator!=(const Measure &right) const {
  return !(*this == right); // still check units
}

bool Measure::operator!() const {
  return (!value);
}

Measure::operator bool() const {
  return (value != 0);
}

// Utility Functions

int Measure::Sign() const {
  if (value > 0)
    return 1;
  else if (value == 0)
    return 0;
  else
    return -1;
}

bool checkUnits(const Measure &one, const Measure &two) {
  return one.factors == two.factors;
}

ostream &operator<<(ostream &sout, const Measure &meas) {
  sout << meas.value;
  if (meas.factors == Dimensions(0, 0, 0))
    return sout;

  if (meas.factors.dist == 1)
    sout << " m";
  else if (meas.factors.dist != 0)
    sout << " m^" << meas.factors.dist;

  if (meas.factors.time == 1)
    sout << " s";
  else if (meas.factors.time != 0)
    sout << " s^" << meas.factors.dist;

  if (meas.factors.mass == 1)
    sout << " kg";
  else if (meas.factors.dist != 0)
    sout << " kg^" << meas.factors.dist;

  return sout;
}

/* ----- Dimension Class Functions ----- */

Dimension::Dimension(double distf, double timef, double massf,
		     double nconvert) :
  Measure(Dimensions(distf, timef, massf)) {
  value = nconvert;
}

Dimension::Dimension(Measure &nconvert) :
  Measure(nconvert) {
  value = nconvert();
}

double Dimension::operator()() const {
  return value;
}

