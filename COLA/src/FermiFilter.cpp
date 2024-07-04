//
// Created by Artem Novikov on 12.06.2024.
//

#include "FermiFilter.hh"

#include "Utilities/NucleiProperties/NucleiProperties.h"

std::unique_ptr<cola::EventData> FermiConverter::operator()(std::unique_ptr<cola::EventData> data) {
  cola::EventParticles result_particles;
  for (auto& particle : data->particles) {
    auto[A, Z] = cola::pdgToAZ(particle.pdgCode);
    auto mass_number = MassNumber(A);
    auto charge_number = ChargeNumber(Z);
    auto momentum = Vector3(particle.pX, particle.pY, particle.pZ);
    auto mass = properties::NucleiProperties()->GetNuclearMass(mass_number, charge_number);

    /// apply model
    auto result = model_.BreakItUp(
        fermi::FermiParticle(
            mass_number,
            charge_number,
            LorentzVector(momentum, std::sqrt(std::pow(mass, 2) + momentum.mag2()))
        )
    );

    /// convert model's results to cola format
    for (auto& fragment : result) {
      result_particles.emplace_back(
          cola::Particle{
              .x=0,
              .y=0,
              .z=0,
              .pX=fragment.GetMomentum().x(),
              .pY=fragment.GetMomentum().y(),
              .pZ=fragment.GetMomentum().z(),
              .pdgCode=cola::AZToPdg(std::make_pair<int, int>(fragment.GetMassNumber(), fragment.GetChargeNumber())),
              .pClass=cola::ParticleClass::produced,
          }
      );
    }
  }

  data->particles = std::move(result_particles);
  return data;
}