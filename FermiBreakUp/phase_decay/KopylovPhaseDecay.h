//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_KOPYLOVPhaseDecay_H
#define FERMIBREAKUP_PHASE_DECAY_KOPYLOVPhaseDecay_H

#include "VPhaseDecay.h"

namespace fbu {
  class KopylovPhaseDecay : public VPhaseDecay{
  public:
    std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const override;
  };
} // namespace fbu

#endif // FERMIBREAKUP_PHASE_DECAY_KOPYLOVPhaseDecay_H
