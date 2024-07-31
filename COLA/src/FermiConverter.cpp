//
// Created by Artem Novikov on 12.06.2024.
//

#include <FermiBreakUp.h>
#include <Utilities/NucleiProperties/NucleiProperties.h>

#include "FermiConverter.h"

using namespace cola;

namespace {
  fermi::Particle ColaToFermi(const cola::Particle& particle) {
    auto [A, Z] = cola::pdgToAZ(particle.pdgCode);
    auto mass_number = MassNumber(A);
    auto charge_number = ChargeNumber(Z);
    auto momentum = Vector3(particle.pX, particle.pY, particle.pZ);
    auto mass = properties::NucleiProperties()->GetNuclearMass(mass_number, charge_number);

    return fermi::Particle(
      mass_number,
      charge_number,
      LorentzVector(momentum, std::sqrt(std::pow(mass, 2) + momentum.mag2()))
    );
  }

  cola::Particle FermiToCola(const fermi::Particle& particle) {
    return cola::Particle{
      .x=0,
      .y=0,
      .z=0,
      .pX=particle.GetMomentum().x(),
      .pY=particle.GetMomentum().y(),
      .pZ=particle.GetMomentum().z(),
      .pdgCode=cola::AZToPdg({
        static_cast<int>(particle.GetMassNumber()),
        static_cast<int>(particle.GetChargeNumber())
      }),
      .pClass=cola::ParticleClass::produced,
    };
  }
}

FermiConverter::FermiConverter(std::unique_ptr<fermi::FermiBreakUp>&& model) : model_(std::move(model)) {}

std::unique_ptr<cola::EventData> FermiConverter::operator()(std::unique_ptr<cola::EventData>&& data) {
  cola::EventParticles results;
  for (const auto& particle : data->particles) {
    /// apply model
    auto model_result = model_->BreakItUp(ColaToFermi(particle));

    /// convert model's results to cola format
    for (const auto& fragment : model_result) {
      results.emplace_back(FermiToCola(fragment));
    }
  }

  data->particles = std::move(results);
  return std::move(data);
}
