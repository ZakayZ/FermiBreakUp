//
// Created by Artem Novikov on 07.03.2023.
//

#include "DataTypes.h"

using namespace fermi;

std::string std::to_string(AtomicMass mass) {
  return std::to_string(AtomicMass::ValueType(mass));
}

std::string std::to_string(ChargeNumber charge) {
  return std::to_string(ChargeNumber::ValueType(charge));
}

std::ostream& operator<<(std::ostream& out, const AtomicMass& mass) {
  out << AtomicMass::ValueType(mass);
  return out;
}

std::istream& operator>>(std::istream& in, AtomicMass& mass) {
  AtomicMass::ValueType val;
  in >> val;
  mass = AtomicMass(val);
  return in;
}

std::ostream& operator<<(std::ostream& out, const ChargeNumber& charge) {
  out << ChargeNumber::ValueType(charge);
  return out;
}

std::istream& operator>>(std::istream& in, ChargeNumber& charge) {
  ChargeNumber::ValueType val;
  in >> val;
  charge = ChargeNumber(val);
  return in;
}
