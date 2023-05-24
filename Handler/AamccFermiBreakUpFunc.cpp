//
// Created by Artem Novikov on 24.05.2023.
//

#include <vector>

#include "G4Fragment.hh"
#include "AamccFermiBreakUpFunc.h"
#include "FermiBreakUp.h"

AAMCCFermiBreakUp::AAMCCFermiBreakUp() : fermi_model_(std::make_unique<FermiBreakUp>()) {}

AAMCCFermiBreakUp::AAMCCFermiBreakUp(std::unique_ptr<VFermiBreakUp>&& model) : fermi_model_(std::move(model)) {}

G4FragmentVector* AAMCCFermiBreakUp::BreakItUp(const G4Fragment& fragment) {
  auto results = fermi_model_->BreakItUp(FermiParticle(MassNumber(fragment.GetA_asInt()),
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
