//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_DECAY_H
#define FERMIBREAKUP_PHASE_DECAY_DECAY_H

#include "VDecay.h"

namespace fermi {

  class Decay : public VDecay {
  public:
    std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const override;
  };

} // namespace fermi

#endif // FERMIBREAKUP_PHASE_DECAY_DECAY_H
