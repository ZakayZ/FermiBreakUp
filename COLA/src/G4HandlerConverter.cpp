#include <COLA.hh>
#include <G4NucleiProperties.hh>
#include <ExcitationHandler.h>

#include "G4HandlerConverter.h"

using namespace cola;

namespace {
  G4Fragment ColaToG4(const cola::Particle& particle) {
    auto [A, Z] = cola::pdgToAZ(particle.pdgCode);
    auto mass = G4NucleiProperties::GetNuclearMass(A, Z);

    G4ThreeVector momentum(particle.pX, particle.pY, particle.pZ);
    return G4Fragment(
        G4int(A),
        G4int(Z),
        G4LorentzVector(momentum, std::sqrt(std::pow(mass, 2) + momentum.mag2()))
    );
  }

  cola::Particle G4ToCola(const G4ReactionProduct& fragment) {
    return cola::Particle{
      .x=0,
      .y=0,
      .z=0,
      .pX=fragment.GetMomentum().x(),
      .pY=fragment.GetMomentum().y(),
      .pZ=fragment.GetMomentum().z(),
      .pdgCode=cola::AZToPdg({
        static_cast<int>(fragment.GetDefinition()->GetAtomicNumber()),
        static_cast<int>(fragment.GetDefinition()->GetPDGCharge())
      }),
      .pClass=cola::ParticleClass::produced,
    };
  }
}

G4HandlerConverter::G4HandlerConverter(std::unique_ptr<ExcitationHandler>&& model) : model_(std::move(model)) {}

std::unique_ptr<cola::EventData> G4HandlerConverter::operator()(std::unique_ptr<cola::EventData>&& data) {
  cola::EventParticles results;
  for (const auto& particle : data->particles) {
    /// apply model
    auto model_result = model_->BreakItUp(ColaToG4(particle));

    /// convert model's results to cola format
    for (const auto& fragment : model_result) {
      results.emplace_back(G4ToCola(fragment));
    }
  }

  data->particles = std::move(results);
  return std::move(data);
}
