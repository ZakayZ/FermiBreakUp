//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H

#include "VDecay.h"
#include "KopylovDecay.h"

namespace fbu {

  using FermiPhaseSpaceDecay = KopylovDecay; // or just Decay

  static_assert(std::is_base_of<VDecay, FermiPhaseSpaceDecay>::value, "Invalid phase sampler");

} // namespace fbu

#endif // FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H
