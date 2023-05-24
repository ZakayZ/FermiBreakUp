//
// Created by Artem Novikov on 20.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_

#include <memory>

#include <G4VFermiBreakUp.hh>
#include "MyFermiBreakUp/VFermiBreakUp.h"

class AAMCCFermiBreakUp : public G4VFermiBreakUp {
 public:
  AAMCCFermiBreakUp();

  AAMCCFermiBreakUp(std::unique_ptr<VFermiBreakUp>&& model);

  G4FragmentVector* BreakItUp (const G4Fragment& fragment) override;

 private:
  std::unique_ptr<VFermiBreakUp> fermi_model_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_
