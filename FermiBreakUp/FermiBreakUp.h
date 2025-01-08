//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFERMIBREAKUPH_
#define FERMIBREAKUPMYFERMIBREAKUPFERMIBREAKUPH_

#include <memory>

#include "Particle.h"

#include "VConfigurations.h"
#include "configurations/Configurations.h"

#include "VFermiBreakUp.h"

namespace fermi {

  class FermiBreakUp : public VFermiBreakUp {
  public:
    FermiBreakUp();

    FermiBreakUp(std::unique_ptr<VConfigurations>&& Configurations);

    ParticleVector BreakItUp(const Particle& nucleus) override final;

    ~FermiBreakUp() = default;

    static std::unique_ptr<VConfigurations> DefaultConfigurations();

  private:
    std::unique_ptr<VConfigurations> fermiConfigurations_;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFERMIBREAKUPH_
