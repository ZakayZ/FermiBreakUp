//
// Created by Artem Novikov on 20.05.2023.
//

#include <vector>

#include "AAMCCFermiBreakUp.h"
#include "FermiBreakUp.h"

class G4Fragment;
using G4FragmentVector = std::vector<G4Fragment*>;

G4FragmentVector* AAMCCFermiBreakUp::BreakItUp(const G4Fragment& fragment) {
  auto results = FermiBreakUp::BreakItUp(FermiParticle(MassNumber(fragment.GetA_asInt()),
                                                       ChargeNumber(fragment.GetZ_asInt()),
                                                       fragment.GetMomentum()));

  auto g4_results = new G4FragmentVector();
  g4_results->reserve(results.size());

  for (auto& particle : results) {
    g4_results->push_back(new G4Fragment(G4int(particle.GetMassNumber()),
                                        G4int(particle.GetChargeNumber()),
                                        G4LorentzVector(particle.GetMomentum())));
  }

  return g4_results;
}
