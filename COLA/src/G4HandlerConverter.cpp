#include <COLA.hh>
#include <G4NucleiProperties.hh>
#include <ExcitationHandler.h>

#include "G4HandlerConverter.h"

using namespace cola;

namespace {
  G4Fragment ColaToG4(const cola::Particle& particle) {
    auto [A, Z] = particle.getAZ();

    return G4Fragment(
      G4int(A),
      G4int(Z),
      G4LorentzVector(
        particle.momentum.x,
        particle.momentum.y,
        particle.momentum.z,
        particle.momentum.e
      )
    );
  }

  cola::Particle G4ToCola(const G4ReactionProduct& fragment) {
    return cola::Particle{
      .position=cola::LorentzVector{
        .t=0,
        .x=0,
        .y=0,
        .z=0,
      },
      .momentum=cola::LorentzVector{
        .e=fragment.GetTotalEnergy(),
        .x=fragment.GetMomentum().x(),
        .y=fragment.GetMomentum().y(),
        .z=fragment.GetMomentum().z(),
      },
      .pdgCode=cola::AZToPdg({
        static_cast<int>(fragment.GetDefinition()->GetAtomicMass()),
        static_cast<int>(fragment.GetDefinition()->GetAtomicNumber())
      }),
      .pClass=cola::ParticleClass::produced,
    };
  }
}

G4HandlerConverter::G4HandlerConverter(std::unique_ptr<ExcitationHandler>&& model) : model_(std::move(model)) {}

std::unique_ptr<cola::EventData> G4HandlerConverter::operator()(std::unique_ptr<cola::EventData>&& data) {
  cola::EventParticles results;
  for (const auto& particle : data->particles) {
    // apply model
    auto modelResult = model_->BreakItUp(ColaToG4(particle));

    // convert model's results to cola format
    for (const auto& fragment : modelResult) {
      results.emplace_back(G4ToCola(fragment));
    }
  }

  data->particles = std::move(results);
  return std::move(data);
}
