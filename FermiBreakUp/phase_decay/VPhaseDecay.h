//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_VPHASEDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_VPHASEDECAY_H

#include <vector>
#include "FermiBreakUp/util/DataTypes.h"

namespace fbu {
  class VPhaseDecay {
  public:
    virtual std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const = 0;

    virtual ~VPhaseDecay() = default;
  };
} // namespace fbu

#endif // FERMIBREAKUP_PHASE_DECAY_VPHASEDECAY_H
