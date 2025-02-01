//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_DATATYPES_H
#define FERMIBREAKUP_UTILITIES_DATATYPES_H

#include <CLHEP/Vector/LorentzVector.h>

#include <memory>
#include <string>

namespace fbu {
  using FermiInt = int32_t;

  using FermiUInt = uint32_t;

  using FermiFloat = double;

  using LorentzVector = CLHEP::HepLorentzVector;

  using Vector3 = CLHEP::Hep3Vector;

  using ParticleMomentum = Vector3;

  using FermiStr = std::string;

  template <typename Key, typename Value>
  class VCache {
  public:
    virtual std::shared_ptr<Value> Insert(const Key& key, Value&& value) = 0;
    virtual std::shared_ptr<Value> Get(const Key& key) = 0;
    virtual ~VCache() = default;
  };

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
    ValueType mass_;
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
    ValueType charge_;
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

} // namespace fbu

namespace std {
  template <>
  struct hash<::fbu::NucleiData> {
    size_t operator()(const ::fbu::NucleiData& key) const
    {
      auto mass = ::fbu::FermiInt(key.atomicMass);
      auto charge = ::fbu::FermiInt(key.chargeNumber);
      return (mass * (mass + 1)) / 2 + charge;
    }
  };

  string to_string(::fbu::AtomicMass mass);
  string to_string(::fbu::ChargeNumber charge);

  std::ostream& operator<<(std::ostream& out, const ::fbu::AtomicMass& mass);
  std::istream& operator>>(std::istream& in, ::fbu::AtomicMass& mass);

  std::ostream& operator<<(std::ostream& out, const ::fbu::ChargeNumber& charge);
  std::istream& operator>>(std::istream& in, ::fbu::ChargeNumber& charge);
}

constexpr fbu::AtomicMass operator ""_m(unsigned long long mass) {
  return fbu::AtomicMass(mass);
}

constexpr fbu::ChargeNumber operator ""_c(unsigned long long charge) {
  return fbu::ChargeNumber(charge);
}

#endif // FERMIBREAKUP_UTILITIES_DATATYPES_H
