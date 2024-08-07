//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMIPHASESPACEDECAY_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMIPHASESPACEDECAY_H_

#include "VDecay.h"
#include "Decay.h"
#include "KopylovDecay.h"

namespace fermi {

    using FermiPhaseSpaceDecay = KopylovDecay; /// or just Decay

    static_assert(std::is_base_of<VDecay, FermiPhaseSpaceDecay>::value, "Incorrect phase sampler");

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_FERMIPHASESPACEDECAY_H_
