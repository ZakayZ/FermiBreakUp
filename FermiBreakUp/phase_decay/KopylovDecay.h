//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_KOPYLOVDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_KOPYLOVDECAY_H

#include "VDecay.h"

namespace fbu {

  class KopylovDecay : public VDecay{
  public:
    std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const override;
  };

} // namespace fbu

#endif // FERMIBREAKUP_PHASE_DECAY_KOPYLOVDECAY_H
