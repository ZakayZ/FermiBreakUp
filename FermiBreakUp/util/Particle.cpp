//
// Created by Artem Novikov on 17.02.2023.
//

#include <iomanip>
#include <CLHEP/Units/PhysicalConstants.h>

#include "nuclei_properties/NucleiProperties.h"
#include "Particle.h"

using namespace fermi;

Particle::Particle(AtomicMass atomicMass, ChargeNumber chargeNumber, const LorentzVector& momentum)
    : atomicMass_(atomicMass), chargeNumber_(chargeNumber), momentum_(momentum) {
  CalculateGroundStateMass();
  CalculateExcitationEnergy();
}

NucleiData Particle::GetNucleiData() const {
  return {atomicMass_, chargeNumber_};
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

FermiFloat Particle::GetBindingEnergy() const {
  return (FermiUInt(atomicMass_) - FermiUInt(chargeNumber_)) * CLHEP::neutron_mass_c2
      + FermiFloat(chargeNumber_) * CLHEP::proton_mass_c2 - groundStateMass_;
}

bool Particle::IsStable() const {
  return excitationEnergy_ <= 0;
}

void Particle::SetMassAndCharge(AtomicMass atomicMass, ChargeNumber chargeNumber) {
  atomicMass_ = atomicMass;
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
  groundStateMass_ = properties::NucleiProperties()->GetNuclearMass(atomicMass_, chargeNumber_);
}

std::ostream& operator<<(std::ostream& out, const Particle& particle) {
  auto oldFloatField = out.flags();
  out.setf(std::ios::floatfield);

  out << "Fragment: A = " << std::setw(3) << particle.GetAtomicMass()
      << ", Z = " << std::setw(3) << particle.GetChargeNumber();
  out.setf(std::ios::scientific, std::ios::floatfield);

  auto oldUserPrecision = out.precision();

  out << std::setprecision(3)
      << ", U = " << particle.GetExcitationEnergy() / CLHEP::MeV
      << " MeV  IsGroundState= " << particle.IsStable() << '\n'
      << "          P = ("
      << particle.GetMomentum().x() / CLHEP::MeV << ","
      << particle.GetMomentum().y() / CLHEP::MeV << ","
      << particle.GetMomentum().z() / CLHEP::MeV
      << ") MeV   E = "
      << particle.GetMomentum().t() / CLHEP::MeV << " MeV"
      << std::endl;

  out.setf(oldFloatField, std::ios::floatfield);
  out.precision(oldUserPrecision);

  return out;
}
