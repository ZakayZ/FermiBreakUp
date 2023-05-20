//
// Created by Artem Novikov on 20.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_

#include <G4VFermiBreakUp.hh>

class AAMCCFermiBreakUp : public G4VFermiBreakUp {
 public:
  G4FragmentVector* BreakItUp (const G4Fragment& fragment) override;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_AAMCCFERMIBREAKUP_H_
