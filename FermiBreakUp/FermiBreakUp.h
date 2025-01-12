//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_FERMIBREAKUP_H
#define FERMIBREAKUP_FERMIBREAKUP_H

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

#endif // FERMIBREAKUP_FERMIBREAKUP_H
