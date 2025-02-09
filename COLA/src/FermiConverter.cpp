//
// Created by Artem Novikov on 12.06.2024.
//

#include <FermiBreakUp.h>
#include <nuclei_properties/NucleiProperties.h>

#include "FermiConverter.h"

using cola::FermiConverter;

namespace {
  fbu::Particle ColaToFermi(const cola::Particle& particle) {
    auto [A, Z] = particle.getAZ();
    auto atomicMass = AtomicMass(A);
    auto chargeNumber = ChargeNumber(Z);

    return fbu::Particle(
      atomicMass,
      chargeNumber,
      LorentzVector(
        particle.momentum.x,
        particle.momentum.y,
        particle.momentum.z,
        particle.momentum.e
      )
    );
  }

  cola::Particle FermiToCola(const fbu::Particle& particle) {
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
        static_cast<int>(particle.GetAtomicMass()),
        static_cast<int>(particle.GetChargeNumber())
      }),
      .pClass=cola::ParticleClass::produced,
    };
  }
}

FermiConverter::FermiConverter(std::unique_ptr<fbu::FermiBreakUp>&& model) : model_(std::move(model)) {}

std::unique_ptr<cola::EventData> FermiConverter::operator()(std::unique_ptr<cola::EventData>&& data) {
  cola::EventParticles results;
  for (const auto& particle : data->particles) {
    // apply model
    auto modelResult = model_->BreakItUp(ColaToFermi(particle));

    // convert model's results to cola format
    for (const auto& fragment : modelResult) {
      results.emplace_back(FermiToCola(fragment));
    }
  }

  data->particles = std::move(results);
  return std::move(data);
}
