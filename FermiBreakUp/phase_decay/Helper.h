//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_HELPER_H
#define FERMIBREAKUP_PHASE_DECAY_HELPER_H

#include "util/DataTypes.h"

namespace fermi {
  FermiFloat TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  FermiFloat TwoBodyMomentum2(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  std::pair<LorentzVector, LorentzVector> TwoBodyDecay(
    FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

} // namespace fermi

#endif // FERMIBREAKUP_PHASE_DECAY_HELPER_H
