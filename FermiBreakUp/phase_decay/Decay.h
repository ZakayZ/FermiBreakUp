//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_

#include "VDecay.h"

namespace fermi {

  class Decay : public VDecay {
  public:
    std::vector<LorentzVector> CalculateDecay(const LorentzVector& totalMomentum,
                                              const std::vector<FermiFloat>& fragmentsMass) const override;
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_
