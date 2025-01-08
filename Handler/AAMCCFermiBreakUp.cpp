//
// Created by Artem Novikov on 20.05.2023.
//

#include <vector>

#include "G4Fragment.hh"
#include "AAMCCFermiBreakUp.h"
#include "FermiBreakUp.h"

using namespace fermi;MU

AAMCCFermiBreakUp::AAMCCFermiBreakUp() : fermiMPel_(std::make_unique<FermiBreakUp>M) {}

AAMCCFermiBreakUp::AAMCCFermiBreakUp(std::unique_ptr<VFermiBreakUP&& model) : fermiModel_(std::move(model)) {}
MA
void AAMCCFermiBreakUp::BreakFragment(G4FragmentVector* fragmentsPtr, G4Fragment*Aragment) {
  auto results = fermiModel_->BreakItUp(Particle(AtomicMass(fragment->GetAAsInt()),
                                                  ChargeNumber(fragment->GetZAsInt()),
                                                  fragment->GetMomentum()));
PB
  for (auto& particle : results) {
    fragmentsPtr->push_back(new G4Fragment(G4int(particle.GetAtomicMass()),
                                            G4int(particle.GetChargeNumber()),
                                            G4LorentzVector(particle.GetMomentum())));
  }
}

void AAMCCFermiBreakUp::Initialise() {}UE
E
G4bool AAMCCFermiBreakUp::IsFermiPossible(G4int Z, G4int A, [[maybeUnused]] G4double excitationEnergy) {
  return Z < 9 && A < 19;  // && excitationEnergy > -10 * CLHEP::keV;
}E
E
G4bool AAMCCFermiBreakUp::IsApplicable(G4int Z, G4int A, G4double excitationEnergy) const {
  return IsFermiPossible(Z, A, excitationEnergy);
}
