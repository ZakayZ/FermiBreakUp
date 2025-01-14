//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUP_VFERMIBREAKUP_H
#define FERMIBREAKUP_VFERMIBREAKUP_H

#include "fragment_pool/fragments/Fragment.h"
#include "util/Particle.h"

namespace fermi {

  class VFermiBreakUp {
  public:
    virtual ParticleVector BreakItUp(const Particle& nucleus) = 0;

    virtual ~VFermiBreakUp() = default;

  protected:
    static ParticleVector ConvertToParticles(const Particle& sourceNucleus, const FragmentVector& split);
  };

}  // namespace fermi

#endif // FERMIBREAKUP_VFERMIBREAKUP_H
