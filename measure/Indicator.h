/******************************************************************************\
 * Indicator: a class of measurements
 ******************************************************************************
 *
\******************************************************************************/

#ifndef INDICATOR_H
#define INDICATOR_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include "Unit.h"

using namespace std;

namespace openworld {
  class Indicator {
  protected:
    string name;
    Unit unit;
    double min;
    double max;

    Indicator(string name, Unit unit, double min, double max)
      : unit(unit) {
      this->name = name;
      this->min = min;
      this->max = max;
    }

  public:
    string getName() const {
      return name;
    }

    const Unit& getUnit() const {
      return unit;
    }

    double getMin() const {
      return min;
    }

    double getMax() const {
      return max;
    }

    virtual double getRandomValue() {
      double f = (double) rand() / RAND_MAX;
      return f*(max - min) + min;
    }

    // Conversions
    virtual bool isConvertible() const {
      return false;
    }

    const Unit& getStandardUnit() const {
      return unit.getStandardUnit();
    }

    virtual double convertToStandardIndicator(double from) const {
      throw runtime_error("Cannot convert to standard indicator.");
    }

    virtual double convertFromStandardIndicator(double to) const {
      throw runtime_error("Cannot convert to standard indicator.");
    }

    friend ostream& operator<<(ostream& out, const Indicator& xx) {
      return out << xx.name << " [" << xx.unit << "]";
    }

    bool operator==(const Indicator& b) const {
      return (this == &b || (name == b.name && unit == b.unit));
    }

    bool operator!=(const Indicator& b) const {
      return !(*this == b);
    }

    // Mathematics

    friend Indicator operator-(const Indicator& a) {
      return Indicator("-" + a.name, a.unit, -a.max, -a.min);
    }

    Indicator operator+(const Indicator& b) const {
      if (unit != b.unit)
        throw runtime_error("unit mismatch to +");
      return Indicator("(" + name + " + " + b.name + ")", unit, min + b.min, max + b.max);
    }

    Indicator operator-(const Indicator& b) const {
      if (unit != b.unit)
        throw runtime_error("unit mismatch to -");
      return Indicator("(" + name + " - " + b.name + ")", unit, min - b.min, max - b.max);
    }

    Indicator operator*(const Indicator& b) const {
      double newmin = std::min(min * b.min, std::min(min * b.max, b.min * max));
      double newmax = std::max(max * b.max, min * b.min);
      return Indicator(name + " " + b.name, unit * b.unit, newmin, newmax);
    }

    Indicator operator/(const Indicator& b) const {
      double newmin = std::min(min / b.min, std::min(min / b.max, b.min / max));
      double newmax = std::max(max / b.max, min / b.min);
      return Indicator("(" + name + ")/(" + b.name + ")", unit / b.unit, newmin, newmax);
    }

    // Serialization

    virtual ostream& streamInsert(ostream& os) const {
      return unit.streamInsert(os) << name << endl << min << " " << max << " ";
    }

    static Indicator streamExtract(istream& in) {
      Unit unit = Unit::streamExtract(in);
      string name;
      getline(in, name);

      double min, max;
      in >> min >> max;

      return Indicator(name, unit, min, max);
    }
  };

  // floating point value
  class LinearIndicator : public Indicator {
  protected:
    double standardShift;

  public:
  LinearIndicator(string name, Unit unit, double min, double max, double shift = 0)
    : Indicator(name, unit, min, max) {
      this->standardShift = shift;
    }

    LinearIndicator shiftedIndicator(double amount) {
      if (amount < 0)
        return LinearIndicator(name + to_string(amount), unit, min + amount, min + amount);
      else
        return LinearIndicator(name + "+" + to_string(amount), unit, min + amount, min + amount);
    }

    virtual bool isConvertible() const {
      return true;
    }

    virtual double convertToStandardIndicator(double from) const {
      return unit.convertToStandardUnits(from - standardShift);
    }

    virtual double convertfromStandardIndicator(double to) const {
      return unit.convertFromStandardUnits(to) + standardShift;
    }
  };
}

#endif
