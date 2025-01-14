//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_FERMIBREAKUP_H
#define FERMIBREAKUP_FERMIBREAKUP_H

#include <memory>

#include "util/Particle.h"

#include "configurations/VConfigurations.h"
#include "configurations/impl/Configurations.h"

#include "VFermiBreakUp.h"

namespace fermi {

  class FermiBreakUp : public VFermiBreakUp {
  public:
    FermiBreakUp();

    FermiBreakUp(std::unique_ptr<VConfigurations>&& configurations);

    ParticleVector BreakItUp(const Particle& nucleus) override;

    ~FermiBreakUp() = default;

    static std::unique_ptr<VConfigurations> DefaultConfigurations();

  private:
    std::unique_ptr<VConfigurations> configurations_;
  };

} // namespace fermi

#endif // FERMIBREAKUP_FERMIBREAKUP_H
