//
// Created by Artem Novikov on 07.03.2023.
//

#include "DataTypes.h"

using namespace fbu;

FermiStr std::to_string(AtomicMass mass) {
  return std::to_string(AtomicMass::ValueType(mass));
}

FermiStr std::to_string(ChargeNumber charge) {
  return std::to_string(ChargeNumber::ValueType(charge));
}

std::ostream& std::operator<<(std::ostream& out, const AtomicMass& mass) {
  out << AtomicMass::ValueType(mass);
  return out;
}

std::istream& std::operator>>(std::istream& in, AtomicMass& mass) {
  AtomicMass::ValueType val;
  in >> val;
  mass = AtomicMass(val);
  return in;
}

std::ostream& std::operator<<(std::ostream& out, const ChargeNumber& charge) {
  out << ChargeNumber::ValueType(charge);
  return out;
}

std::istream& std::operator>>(std::istream& in, ChargeNumber& charge) {
  ChargeNumber::ValueType val;
  in >> val;
  charge = ChargeNumber(val);
  return in;
}
