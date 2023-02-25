//
// Created by Artem Novikov on 17.02.2023.
//

#include <iomanip>
#include <CLHEP/Units/PhysicalConstants.h>

#include "Utilities/NucleiProperties.h"
#include "FermiParticle.h"

FermiParticle::FermiParticle(uint32_t mass_number, uint32_t charge_number, const LorentzVector& momentum)
    : mass_number_(mass_number), charge_number_(charge_number), momentum_(momentum), angular_momentum_() {
  excitation_energy_ = 0.0;
  ground_state_mass_ = 0.0;
  if (GetMassNumber() > 0) {
    CalculateGroundStateMass();
    CalculateExcitationEnergy();
  }
}

uint32_t FermiParticle::GetMassNumber() const {
  return mass_number_;
}

uint32_t FermiParticle::GetChargeNumber() const {
  return charge_number_;
}

const LorentzVector& FermiParticle::GetMomentum() const {
  return momentum_;
}

const Vector3& FermiParticle::GetAngularMomentum() const {
  return angular_momentum_;
}

FermiFloat FermiParticle::GetExcitationEnergy() const {
  return excitation_energy_;
}

FermiFloat FermiParticle::GetGroundStateMass() const {
  return ground_state_mass_;
}

FermiFloat FermiParticle::GetBindingEnergy() const {
  return (mass_number_ - charge_number_) * CLHEP::neutron_mass_c2 + charge_number_ * CLHEP::proton_mass_c2
      - ground_state_mass_;
}

bool FermiParticle::IsStable() const {
  return excitation_energy_ <= 0;
}

void FermiParticle::SetMassAndCharge(uint32_t mass_number, uint32_t charge_number) {
  mass_number_ = mass_number;
  charge_number_ = charge_number;
  CalculateGroundStateMass();
}

void FermiParticle::SetMomentum(const LorentzVector& momentum) {
  momentum_ = momentum;
  CalculateExcitationEnergy();
}

void FermiParticle::SetAngularMomentum(const Vector3& angular_momentum) {
  angular_momentum_ = angular_momentum;
}

void FermiParticle::CalculateExcitationEnergy() {
  excitation_energy_ = momentum_.mag() - ground_state_mass_;
  if (excitation_energy_ < 0) { ExcitationEnergyWarning(); }
}

void FermiParticle::CalculateGroundStateMass() {
  ground_state_mass_ = NucleiProperties::GetNuclearMass(mass_number_, charge_number_);
}

void FermiParticle::ExcitationEnergyWarning() {
  if (excitation_energy_ < -10 * CLHEP::eV) {
    std::cout << "G4Fragment::CalculateExcitationEnergy(): WARNING " << std::endl << *this << std::endl;
  }
  excitation_energy_ = 0;  /// TODO Investigate
}

std::ostream& operator<<(std::ostream& out, const FermiParticle& particle) {
  auto old_floatfield = out.flags();
  out.setf(std::ios::floatfield);

  out << "Fragment: A = " << std::setw(3) << particle.GetMassNumber()
      << ", Z = " << std::setw(3) << particle.GetChargeNumber();
  out.setf(std::ios::scientific, std::ios::floatfield);

  // Store user's precision setting and reset to (3) here: back-compatibility
  std::streamsize old_user_precision = out.precision();

  out << std::setprecision(3)
      << ", U = " << particle.GetExcitationEnergy() / CLHEP::MeV
      << " MeV  IsStable= " << particle.IsStable() << std::endl
      << "          P = ("
      << particle.GetMomentum().x() / CLHEP::MeV << ","
      << particle.GetMomentum().y() / CLHEP::MeV << ","
      << particle.GetMomentum().z() / CLHEP::MeV
      << ") MeV   E = "
      << particle.GetMomentum().t() / CLHEP::MeV << " MeV"
      << std::endl;

  /// What about Angular momentum???

  out.setf(old_floatfield, std::ios::floatfield);
  out.precision(old_user_precision);

  return out;
}
