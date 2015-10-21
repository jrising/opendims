// measure.h - Class declarations for the Mechanical Measures Class
//   makes functions formal by requiring appropriate units

#ifndef MEASURE_H
#define MEASURE_H

/* Here's an example of what one can do with measures:
  Measure mass1(kg), mass2(kg);
  Measure distance1(m), distance2(m);
  Measure totalmoment(kg * Sqr(m));

  mass1 = 1.0 * kg;
  mass2 = 2.0 * kg;
  distance1 = 3.0 * m;
  distance2 = 2.0 * m;

  totalmoment = mass1 * Sqr(distance1) + mass2 * Sqr(distance2);
  cout << totalmoment << endl;  // 17.0 kg m^2;

  totalmoment = mass1 * Sqr(distance1) + mass2 * distance2; // error
  cout << totalmoment << endl;
*/

#include <iostream.h>
#include <fstream.h>
#include <math.h>

#define bool char
#define dimerror(errorstr) { cout << "Units error in " << errorstr; exit(1); }

/* ----- Accessory structure ----- */

// Dimensions holds the dimensions of a measure
class Dimensions {
public:
  Dimensions(float ndist, float ntime, float nmass);
  bool operator==(const Dimensions &right) const;

  float dist;
  float time;
  float mass;
};

/* ----- Measure Class ----- */

class Measure {
  // Mathematical functions (convert more later)
  friend const Measure Sqr(const Measure &);
  friend const Measure Sqrt(const Measure &);
  friend const Measure Pow(const Measure &, const Measure &);

  // If double is first...
  friend const Measure operator*(double, const Measure &);
  friend const Measure operator/(double, const Measure &);

  // Dimension Error checking
  friend bool checkUnits(const Measure &, const Measure &);

  // Output Stream
  friend ostream &operator<<(ostream &, const Measure &);
public:
  Measure(const Measure &);            // Define dimensions
  Measure(double = 0.0);               // For unitless value

  virtual const Measure &operator=(const Measure &); // For setting value

  // Math Operators
  const Measure operator+(const Measure &) const;
  const Measure operator-(const Measure &) const;
  const Measure operator*(const Measure &) const;
  const Measure operator*(double) const;
  const Measure operator/(const Measure &) const;
  const Measure operator/(double) const;
  const Measure operator-() const;

  const Measure operator+=(const Measure &);
  const Measure operator-=(const Measure &);
  // *= and /= change units of measure

  // Relational Operators
  bool operator<(const Measure &) const;
  bool operator>(const Measure &) const;
  bool operator==(const Measure &) const;
  bool operator<=(const Measure &) const;
  bool operator>=(const Measure &) const;
  bool operator!=(const Measure &) const;
  bool operator!() const;
  operator bool() const;

  // Evalution
  virtual double operator()() const;
  double operator()(const Measure &convert) const;

  // Utility Functions
  int Sign() const;
 protected:
  Measure(Dimensions nfactors);        // For setting const factors

  const Dimensions factors;
  double value;
};

/* ---- Dimension Class ----- */

// Dimension class (poorly named) is useful for defining fundamental
// physical dimensions and Measures meant primarily for their
// dimensions not their values
class Dimension : public Measure {
public:
  Dimension(Measure &);              // Meant to hold conversions
  Dimension(double, double, double, double = 1.0); // For base SI

  virtual double operator()() const;
};

static const Dimension k(0, 0, 0);
static const Dimension m(1, 0, 0);
static const Dimension sec(0, 1, 0);
static const Dimension kg(0, 0, 1);

#endif
