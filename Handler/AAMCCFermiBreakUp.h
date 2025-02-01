//
// Created by Artem Novikov on 20.05.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPAAMCCFERMIBREAKUPH_
#define FERMIBREAKUPMYFERMIBREAKUPAAMCCFERMIBREAKUPH_

#include <memory>

#include "G4VFermiBreakUp.hh"
#include "FermiBreakUp.h"

class AAMCCFermiBreakUp : public G4VFermiBreakUp {
 public:
  AAMCCFermiBreakUp() = default;

  AAMCCFermiBreakUp(fbu::FermiBreakUp&& model);

  void Initialise() override;

  void BreakFragment(G4FragmentVector* fragmentsPtr, G4Fragment* fragment) override;

  static G4bool IsFermiPossible(G4int Z, G4int A, G4double excitationEnergy);

  G4bool IsApplicable(G4int Z, G4int A, G4double excitationEnergy) const override;

 private:
  fbu::FermiBreakUp fermiModel_;
};

#endif // FERMIBREAKUPMYFERMIBREAKUPAAMCCFERMIBREAKUPH_
