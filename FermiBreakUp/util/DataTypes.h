//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_DATATYPES_H
#define FERMIBREAKUP_UTILITIES_DATATYPES_H

#include <CLHEP/Vector/LorentzVector.h>

#include <string>

using FermiInt = int32_t;

using FermiUInt = uint32_t;

using FermiFloat = double;

using LorentzVector = CLHEP::HepLorentzVector;

using Vector3 = CLHEP::Hep3Vector;

using ParticleMomentum = Vector3;

class AtomicMass {
 public:
  using value_type = FermiUInt;

  AtomicMass() = default;

  explicit constexpr AtomicMass(value_type mass) : mass_(mass) {}

  AtomicMass(const AtomicMass& other) = default;

  AtomicMass(AtomicMass&& other) = default;

  AtomicMass& operator=(const AtomicMass& other) = default;

  AtomicMass& operator=(AtomicMass&& other) = default;

  constexpr operator FermiUInt() const { return mass_; }

  constexpr operator FermiInt() const { return mass_; }

  constexpr operator FermiFloat() const { return mass_; }

  bool operator<(const AtomicMass& other) const { return mass_ < other.mass_; }

  bool operator>(const AtomicMass& other) const { return mass_ > other.mass_; }

  bool operator<=(const AtomicMass& other) const { return mass_ <= other.mass_; }

  bool operator>=(const AtomicMass& other) const { return mass_ >= other.mass_; }

  bool operator==(const AtomicMass& other) const { return mass_ == other.mass_; }

  bool operator!=(const AtomicMass& other) const { return mass_ != other.mass_; }

 private:
  FermiUInt mass_;
};

constexpr AtomicMass operator ""_m(uint64_t mass) {
  return AtomicMass(mass);
}

namespace std {
  std::string to_string(AtomicMass mass);
}

std::ostream& operator<<(std::ostream& out, const AtomicMass& mass);

std::istream& operator>>(std::istream& in, AtomicMass& mass);

class ChargeNumber {
 public:
  using value_type = FermiUInt;

  ChargeNumber() = default;

  explicit constexpr ChargeNumber(value_type charge) : charge_(charge) {}

  ChargeNumber(const ChargeNumber& other) = default;

  ChargeNumber(ChargeNumber&& other) = default;

  ChargeNumber& operator=(const ChargeNumber& other) = default;

  ChargeNumber& operator=(ChargeNumber&& other) = default;

  constexpr operator FermiUInt() const { return charge_; }

  constexpr operator FermiInt() const { return charge_; }

  constexpr operator FermiFloat() const { return charge_; }

  bool operator<(const ChargeNumber& other) const { return charge_ < other.charge_; }

  bool operator>(const ChargeNumber& other) const { return charge_ > other.charge_; }

  bool operator<=(const ChargeNumber& other) const { return charge_ <= other.charge_; }

  bool operator>=(const ChargeNumber& other) const { return charge_ >= other.charge_; }

  bool operator==(const ChargeNumber& other) const { return charge_ == other.charge_; }

  bool operator!=(const ChargeNumber& other) const { return charge_ != other.charge_; }

 private:
  FermiUInt charge_;
};

constexpr ChargeNumber operator ""_c(uint64_t charge) {
  return ChargeNumber(charge);
}

namespace std {
std::string to_string(ChargeNumber charge);
}

std::ostream& operator<<(std::ostream& out, ChargeNumber charge);

std::istream& operator>>(std::istream& in, ChargeNumber& charge);

struct NucleiData {
  AtomicMass atomicMass;
  ChargeNumber chargeNumber;

  bool operator<(const NucleiData& other) const {
    return atomicMass < other.atomicMass
        || (atomicMass == other.atomicMass && chargeNumber < other.chargeNumber);
  }

  bool operator==(const NucleiData& other) const {
    return atomicMass == other.atomicMass && chargeNumber == other.chargeNumber;
  }

  bool operator!=(const NucleiData& other) const {
    return atomicMass != other.atomicMass || chargeNumber != other.chargeNumber;
  }
};

template <>
struct std::hash<NucleiData>
{
  std::size_t operator()(const NucleiData& key) const
  {
    auto mass = FermiInt(key.atomicMass);
    auto charge = FermiInt(key.chargeNumber);
    return (mass * (mass + 1)) / 2 + charge;
  }
};

#endif // FERMIBREAKUP_UTILITIES_DATATYPES_H
