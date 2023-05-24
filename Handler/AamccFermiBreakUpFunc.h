//
// Created by Artem Novikov on 24.05.2023.
//

#ifndef FERMIBREAKUP_HANDLER_AAMCCFERMIBREAKUPFUNC_H_
#define FERMIBREAKUP_HANDLER_AAMCCFERMIBREAKUPFUNC_H_

#include <memory>

#include "G4VFermiBreakUp.hh"
#include "VFermiBreakUp.h"

class AAMCCFermiBreakUp : public G4VFermiBreakUp {
 public:
  AAMCCFermiBreakUp();

  AAMCCFermiBreakUp(std::unique_ptr<VFermiBreakUp>&& model);

  G4FragmentVector* BreakItUp (const G4Fragment& fragment) override;

 private:
  std::unique_ptr<VFermiBreakUp> fermi_model_;
};


#endif //FERMIBREAKUP_HANDLER_AAMCCFERMIBREAKUPFUNC_H_
