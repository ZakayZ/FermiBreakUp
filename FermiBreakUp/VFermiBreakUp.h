//
// Created by Artem Novikov on 21.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_VFERMIBREAKUP_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_VFERMIBREAKUP_H_

#include "Particle.h"
#include "Split.h"

namespace fermi {

  class VFermiBreakUp {
  public:
    virtual ParticleVector BreakItUp(const Particle& nucleus) = 0;

    virtual ~VFermiBreakUp() = default;

  protected:
    static ParticleVector ConvertToParticles(const Particle& source_nucleus, const FragmentVector& split);
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_VFERMIBREAKUP_H_
