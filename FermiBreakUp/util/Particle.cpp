//
// Created by Artem Novikov on 17.02.2023.
//

#include <iomanip>
#include "Logger.h"
#include <CLHEP/Units/PhysicalConstants.h>

#include "nuclei_properties/NucleiProperties.h"
#include "util/Logger.h"

#include "Particle.h"

using namespace fermi;

Particle::Particle(AtomicMass atomicMass, ChargeNumber chargeNumber, const LorentzVector& momentum)
  : atomicMass_(atomicMass)
  , chargeNumber_(chargeNumber)
  , momentum_(momentum)
  , groundStateMass_(NucleiProperties()->GetNuclearMass(atomicMass_, chargeNumber_))
{
  ASSERT_MSG(FermiUInt(atomicMass_) >= FermiUInt(chargeNumber),
             "imposible particle: A = " << atomicMass_ << ", Z = " << chargeNumber);

  CalculateExcitationEnergy();
}

NucleiData Particle::GetNucleiData() const {
  return {
    atomicMass_,
    chargeNumber_,
  };
}

AtomicMass Particle::GetAtomicMass() const {
  return atomicMass_;
}

ChargeNumber Particle::GetChargeNumber() const {
  return chargeNumber_;
}

const LorentzVector& Particle::GetMomentum() const {
  return momentum_;
}

FermiFloat Particle::GetExcitationEnergy() const {
  return excitationEnergy_;
}

FermiFloat Particle::GetGroundStateMass() const {
  return groundStateMass_;
}

bool Particle::IsStable() const {
  return excitationEnergy_ <= 0.;
}

void Particle::CalculateExcitationEnergy() {
  excitationEnergy_ = momentum_.mag() - groundStateMass_;
  if (excitationEnergy_ < 0.) {
    if (excitationEnergy_ < -10 * CLHEP::eV) {
      LOG_WARN("Excitation Energy is too negative: " << excitationEnergy_ / CLHEP::MeV << " MeV");
    }
    excitationEnergy_ = 0.;
  }
}

std::ostream& std::operator<<(std::ostream& out, const Particle& particle) {
  const auto oldFlags = out.flags();
  const auto oldUserPrecision = out.precision();

  out.setf(std::ios::floatfield);
  out << "FermiParticle: { A = " << particle.GetAtomicMass()
      << ", Z = " << particle.GetChargeNumber();

  out.setf(std::ios::scientific, std::ios::floatfield);
  out << std::setprecision(3)
      << ", U = " << particle.GetExcitationEnergy() / CLHEP::MeV << " MeV"
      << ", IsGroundState = " << (particle.IsStable() ? "yes" : "no")
      << ", P = ("
      << particle.GetMomentum().x() / CLHEP::MeV << ", "
      << particle.GetMomentum().y() / CLHEP::MeV << ", "
      << particle.GetMomentum().z() / CLHEP::MeV
      << ") MeV, E = "
      << particle.GetMomentum().t() / CLHEP::MeV << " MeV}"
      << " }";

  out.setf(oldFlags, std::ios::floatfield);
  out.precision(oldUserPrecision);

  return out;
}
