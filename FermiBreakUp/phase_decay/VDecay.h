//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_VDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_VDECAY_H

#include <vector>
#include "util/DataTypes.h"

namespace fbu {
  class VDecay {
  public:
    virtual std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const = 0;

    virtual ~VDecay() = default;
  };
} // namespace fbu

#endif // FERMIBREAKUP_PHASE_DECAY_VDECAY_H
