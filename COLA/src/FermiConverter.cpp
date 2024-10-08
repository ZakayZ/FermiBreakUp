//
// Created by Artem Novikov on 12.06.2024.
//

#include <FermiBreakUp.h>
#include <Utilities/NucleiProperties/NucleiProperties.h>

#include "FermiConverter.h"

using cola::FermiConverter;

namespace {
  fermi::Particle ColaToFermi(const cola::Particle& particle) {
    auto [A, Z] = particle.getAZ();
    auto mass_number = MassNumber(A);
    auto charge_number = ChargeNumber(Z);

    return fermi::Particle(
      mass_number,
      charge_number,
      LorentzVector(
        particle.momentum.x,
        particle.momentum.y,
        particle.momentum.z,
        particle.momentum.e
      )
    );
  }

  cola::Particle FermiToCola(const fermi::Particle& particle) {
    return cola::Particle{
      .position=cola::LorentzVector{
        .t=0,
        .x=0,
        .y=0,
        .z=0,
      },
      .momentum=cola::LorentzVector{
        .e=particle.GetMomentum().e(),
        .x=particle.GetMomentum().x(),
        .y=particle.GetMomentum().y(),
        .z=particle.GetMomentum().z(),
      },
      .pdgCode=cola::AZToPdg(cola::AZ{
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
