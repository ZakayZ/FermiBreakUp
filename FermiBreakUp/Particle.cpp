//
// Created by Artem Novikov on 17.02.2023.
//

#include <iomanip>
#include <CLHEP/Units/PhysicalConstants.h>

#include "Utilities/NucleiProperties/NucleiProperties.h"
#include "Particle.h"

using namespace fermi;

Particle::Particle(MassNumber massNumber, ChargeNumber chargeNumber, const LorentzVector& momentum)
    : massNumber_(massNumber), chargeNumber_(chargeNumber), momentum_(momentum) {
  CalculateGroundStateMass();
  CalculateExcitationEnergy();
}

NucleiData Particle::GetNucleiData() const {
  return {massNumber_, chargeNumber_};
}


MassNumber Particle::GetMassNumber() const {
  return massNumber_;
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

FermiFloat Particle::GetBindingEnergy() const {
  return (FermiUInt(massNumber_) - FermiUInt(chargeNumber_)) * CLHEP::neutron_mass_c2
      + FermiFloat(chargeNumber_) * CLHEP::proton_mass_c2 - groundStateMass_;
}

bool Particle::IsStable() const {
  return excitationEnergy_ <= 0;
}

void Particle::SetMassAndCharge(MassNumber massNumber, ChargeNumber chargeNumber) {
  massNumber_ = massNumber;
  chargeNumber_ = chargeNumber;
  CalculateGroundStateMass();
}

void Particle::SetMomentum(const LorentzVector& momentum) {
  momentum_ = momentum;
  CalculateExcitationEnergy();
}

void Particle::CalculateExcitationEnergy() {
  excitationEnergy_ = momentum_.mag() - groundStateMass_;
  if (excitationEnergy_ < 0) {
//    if (excitationEnergy_ < -10 * CLHEP::eV) {
//      throw std::runtime_error("Excitation Energy is negative");
//    } // TODO sometimes is raised in collaboration with other models
    excitationEnergy_ = 0;
  }
}

void Particle::CalculateGroundStateMass() {
  groundStateMass_ = properties::NucleiProperties()->GetNuclearMass(massNumber_, chargeNumber_);
}

std::ostream& operator<<(std::ostream& out, const Particle& particle) {
  auto oldFloatField = out.flags();
  out.setf(std::ios::floatfield);

  out << "Fragment: A = " << std::setw(3) << particle.GetMassNumber()
      << ", Z = " << std::setw(3) << particle.GetChargeNumber();
  out.setf(std::ios::scientific, std::ios::floatfield);

  // Store user's precision setting and reset to (3) here: back-compatibility
  std::streamsize oldUserPrecision = out.precision();

  out << std::setprecision(3)
      << ", U = " << particle.GetExcitationEnergy() / CLHEP::MeV
      << " MeV  IsGroundState= " << particle.IsStable() << std::endl
      << "          P = ("
      << particle.GetMomentum().x() / CLHEP::MeV << ","
      << particle.GetMomentum().y() / CLHEP::MeV << ","
      << particle.GetMomentum().z() / CLHEP::MeV
      << ") MeV   E = "
      << particle.GetMomentum().t() / CLHEP::MeV << " MeV"
      << std::endl;

  // What about Angular momentum???

  out.setf(oldFloatField, std::ios::floatfield);
  out.precision(oldUserPrecision);

  return out;
}
