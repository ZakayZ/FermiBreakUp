//
// Created by Artem Novikov on 20.05.2023.
//

#include "G4Fragment.hh"
#include "AAMCCFermiBreakUp.h"
#include "FermiBreakUp.h"

using namespace fbu;

AAMCCFermiBreakUp::AAMCCFermiBreakUp(FermiBreakUp&& model) : fermiModel_(std::move(model)) {}

void AAMCCFermiBreakUp::BreakFragment(G4FragmentVector* fragmentsPtr, G4Fragment* fragment) {
  auto results = fermiModel_.BreakItUp(Particle(MassNumber(fragment->GetA_asInt()),
                                                 ChargeNumber(fragment->GetZ_asInt()),
                                                 fragment->GetMomentum()));

  for (const auto& particle : results) {
    fragmentsPtr->push_back(new G4Fragment(G4int(particle.GetMassNumber()),
                                           G4int(particle.GetChargeNumber()),
                                           G4LorentzVector(particle.GetMomentum())));
  }
}

void AAMCCFermiBreakUp::Initialise() {}

G4bool AAMCCFermiBreakUp::IsFermiPossible(G4int Z, G4int A, [[maybe_unused]] G4double excitationEnergy) {
  return Z < 9 && A < 19;  // && excitationEnergy > -10 * CLHEP::keV;
}

G4bool AAMCCFermiBreakUp::IsApplicable(G4int Z, G4int A, G4double excitationEnergy) const {
  return IsFermiPossible(Z, A, excitationEnergy);
}
