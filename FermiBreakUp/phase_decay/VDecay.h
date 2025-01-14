//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_VDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_VDECAY_H

#include <vector>
#include <optional>
#include "util/DataTypes.h"

namespace fermi {

  FermiFloat TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  std::pair<LorentzVector, LorentzVector> TwoBodyDecay(
    FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  class VDecay {
  public:
    VDecay() = default;

    virtual std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const = 0;

    virtual ~VDecay() = default;
  };

}  // namespace fermi

#endif // FERMIBREAKUP_PHASE_DECAY_VDECAY_H
