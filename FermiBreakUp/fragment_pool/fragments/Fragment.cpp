//
// Created by Artem Novikov on 17.02.2023.
//

#include <iomanip>

#include <CLHEP/Units/PhysicalConstants.h>

#include "FermiBreakUp/nuclei_properties/NucleiProperties.h"

#include "Fragment.h"

using namespace fbu;

Fragment::Fragment(
  AtomicMass atomicMass,
  ChargeNumber chargeNumber,
  FermiInt polarization,
  FermiFloat excitationEnergy
)
  : atomicMass_(atomicMass)
  , chargeNumber_(chargeNumber)
  , polarization_(polarization)
  , excitationEnergy_(excitationEnergy)
{
}

std::vector<Particle> Fragment::GetDecayFragments(const LorentzVector& momentum) const {
  std::vector<Particle> result;
  AppendDecayFragments(momentum, result);
  return result;
}

AtomicMass Fragment::GetAtomicMass() const {
  return atomicMass_;
}

ChargeNumber Fragment::GetChargeNumber() const {
  return chargeNumber_;
}

FermiInt Fragment::GetPolarization() const {
  return polarization_;
}

FermiFloat Fragment::GetExcitationEnergy() const {
  return excitationEnergy_;
}

FermiFloat Fragment::GetMass() const {
  return NucleiProperties()->GetNuclearMass(atomicMass_, chargeNumber_);
}

FermiFloat Fragment::GetTotalEnergy() const {
  return GetMass() + GetExcitationEnergy();
}

std::ostream& std::operator<<(std::ostream& out, const Fragment& fragment) {
  const auto oldFlags = out.flags();
  const auto oldUserPrecision = out.precision();

  out.setf(std::ios::floatfield);
  out << "FermiFragment: { A = " << fragment.GetAtomicMass()
      << ", Z = " << fragment.GetChargeNumber()
      << ", pol = " << fragment.GetPolarization();

  out.setf(std::ios::scientific, std::ios::floatfield);
  out << std::setprecision(3)
      << ", U = " << fragment.GetExcitationEnergy() / CLHEP::MeV
      << " }";

  out.setf(oldFlags, std::ios::floatfield);
  out.precision(oldUserPrecision);

  return out;
}
