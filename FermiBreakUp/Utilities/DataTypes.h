//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPDATATYPESH_
#define FERMIBREAKUPMYFERMIBREAKUPDATATYPESH_

#include <CLHEP/Vector/LorentzVector.h>

using FermiInt = int;

using FermiUInt = uint32_t;

using FermiFloat = double;

using LorentzVector = CLHEP::HepLorentzVector;

using Vector3 = CLHEP::Hep3Vector;

using ParticleMomentum = Vector3;

class MassNumber {
 public:
  using value_type = FermiUInt;

  MassNumber() = default;

  explicit MassNumber(value_type mass) : mass_(mass) {}

  MassNumber(const MassNumber& other) = default;

  MassNumber(MassNumber&& other) = default;

  MassNumber& operator=(const MassNumber& other) = default;

  MassNumber& operator=(MassNumber&& other) = default;

  operator FermiUInt() const { return mass_; }

  operator FermiInt() const { return mass_; }

  operator FermiFloat() const { return mass_; }

  bool operator<(const MassNumber& other) const { return mass_ < other.mass_; }

  bool operator>(const MassNumber& other) const { return mass_ > other.mass_; }

  bool operator<=(const MassNumber& other) const { return mass_ <= other.mass_; }

  bool operator>=(const MassNumber& other) const { return mass_ >= other.mass_; }

  bool operator==(const MassNumber& other) const { return mass_ == other.mass_; }

  bool operator!=(const MassNumber& other) const { return mass_ != other.mass_; }

 private:
  uint32_t mass_;
};

MassNumber operator ""_m(unsigned long long mass);

namespace std {
std::string to_string(MassNumber mass);
}

std::ostream& operator<<(std::ostream& out, const MassNumber& mass);

std::istream& operator>>(std::istream& in, MassNumber& mass);

class ChargeNumber {
 public:
  using value_type = FermiUInt;

  ChargeNumber() = default;

  explicit ChargeNumber(value_type charge) : charge_(charge) {}

  ChargeNumber(const ChargeNumber& other) = default;

  ChargeNumber(ChargeNumber&& other) = default;

  ChargeNumber& operator=(const ChargeNumber& other) = default;

  ChargeNumber& operator=(ChargeNumber&& other) = default;

  operator FermiUInt() const { return charge_; }

  operator FermiInt() const { return charge_; }

  operator FermiFloat() const { return charge_; }

  bool operator<(const ChargeNumber& other) const { return charge_ < other.charge_; }

  bool operator>(const ChargeNumber& other) const { return charge_ > other.charge_; }

  bool operator<=(const ChargeNumber& other) const { return charge_ <= other.charge_; }

  bool operator>=(const ChargeNumber& other) const { return charge_ >= other.charge_; }

  bool operator==(const ChargeNumber& other) const { return charge_ == other.charge_; }

  bool operator!=(const ChargeNumber& other) const { return charge_ != other.charge_; }

 private:
  uint32_t charge_;
};

ChargeNumber operator ""_c(unsigned long long charge);

namespace std {
std::string to_string(ChargeNumber charge);
}

std::ostream& operator<<(std::ostream& out, ChargeNumber charge);

std::istream& operator>>(std::istream& in, ChargeNumber& charge);

struct NucleiData {
  MassNumber massNumber;
  ChargeNumber chargeNumber;

  bool operator<(const NucleiData& other) const {
    return massNumber < other.massNumber
        || (massNumber == other.massNumber && chargeNumber < other.chargeNumber);
  }

  bool operator==(const NucleiData& other) const {
    return massNumber == other.massNumber && chargeNumber == other.chargeNumber;
  }

  bool operator!=(const NucleiData& other) const {
    return massNumber != other.massNumber || chargeNumber != other.chargeNumber;
  }
};

template <>
struct std::hash<NucleiData>
{
  std::size_t operator()(const NucleiData& key) const
  {
    auto mass = FermiInt(key.massNumber);
    auto charge = FermiInt(key.chargeNumber);
    return (mass * (mass + 1)) / 2 + charge;
  }
};

#endif //FERMIBREAKUPMYFERMIBREAKUPDATATYPESH_
