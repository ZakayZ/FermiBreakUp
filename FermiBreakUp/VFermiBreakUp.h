//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPVFERMIBREAKUPH_
#define FERMIBREAKUPMYFERMIBREAKUPVFERMIBREAKUPH_

#include "Particle.h"
#include "Split.h"

namespace fermi {

  class VFermiBreakUp {
  public:
    virtual ParticleVector BreakItUp(const Particle& nucleus) = 0;

    virtual ~VFermiBreakUp() = default;

  protected:
    static ParticleVector ConvertToParticles(const Particle& sourceNucleus, const FragmentVector& split);
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPVFERMIBREAKUPH_
