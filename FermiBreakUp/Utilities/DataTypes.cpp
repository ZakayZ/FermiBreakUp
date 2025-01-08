//
// Created by Artem Novikov on 07.03.2023.
//

#include "DataTypes.h"

ChargeNumber operator ""_c(unsigned long long charge) {
  return ChargeNumber(charge);
}

std::string std::to_string(ChargeNumber charge) {
  return std::to_string(FermiUInt(charge));
}

std::ostream& operator<<(std::ostream& out, ChargeNumber charge) {
  out << FermiUInt(charge);
  return out;
}

std::istream& operator>>(std::istream& in, ChargeNumber& charge) {
  FermiUInt val;
  in >> val;
  charge = ChargeNumber(val);
  return in;
}

AtomicMass operator ""_m(unsigned long long mass) {
  return AtomicMass(mass);
}

std::string std::to_string(AtomicMass mass) {
  return std::to_string(FermiUInt(mass));
}

std::ostream& operator<<(std::ostream& out, const AtomicMass& mass) {
  out << FermiUInt(mass);
  return out;
}

std::istream& operator>>(std::istream& in, AtomicMass& mass) {
  FermiUInt val;
  in >> val;
  mass = AtomicMass(val);
  return in;
}
