//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H
#define FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H

#include "VDecay.h"
#include "Decay.h"
#include "KopylovDecay.h"

namespace fermi {

    using FermiPhaseSpaceDecay = KopylovDecay; // or just Decay

    static_assert(std::is_base_of<VDecay, FermiPhaseSpaceDecay>::value, "Incorrect phase sampler");

}  // namespace fermi

#endif // FERMIBREAKUP_PHASE_DECAY_FERMIPHASESPACEDECAY_H
