//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_DATATYPES_H
#define FERMIBREAKUP_UTILITIES_DATATYPES_H

#include <CLHEP/Vector/LorentzVector.h>

#include <string>

namespace fermi {
  using FermiInt = int32_t;

  using FermiUInt = uint32_t;

  using FermiFloat = double;

  using LorentzVector = CLHEP::HepLorentzVector;

  using Vector3 = CLHEP::Hep3Vector;

  using ParticleMomentum = Vector3;

  class AtomicMass {
  public:
    using ValueType = FermiUInt;

    AtomicMass() = default;

    explicit constexpr AtomicMass(ValueType mass) : mass_(mass) {}

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

  class ChargeNumber {
  public:
    using ValueType = FermiUInt;

    ChargeNumber() = default;

    explicit constexpr ChargeNumber(ValueType charge) : charge_(charge) {}

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

} // namespace fermi

namespace std {
  template <>
  struct hash<fermi::NucleiData> {
    size_t operator()(const fermi::NucleiData& key) const
    {
      auto mass = fermi::FermiInt(key.atomicMass);
      auto charge = fermi::FermiInt(key.chargeNumber);
      return (mass * (mass + 1)) / 2 + charge;
    }
  };

  string to_string(fermi::AtomicMass mass);
  string to_string(fermi::ChargeNumber charge);
}

constexpr fermi::AtomicMass operator ""_m(uint64_t mass) {
  return fermi::AtomicMass(mass);
}

constexpr fermi::ChargeNumber operator ""_c(uint64_t charge) {
  return fermi::ChargeNumber(charge);
}

std::ostream& operator<<(std::ostream& out, const fermi::AtomicMass& mass);
std::istream& operator>>(std::istream& in, fermi::AtomicMass& mass);

std::ostream& operator<<(std::ostream& out, const fermi::ChargeNumber& charge);
std::istream& operator>>(std::istream& in, fermi::ChargeNumber& charge);

#endif // FERMIBREAKUP_UTILITIES_DATATYPES_H
