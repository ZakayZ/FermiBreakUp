//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_

#include <memory>

#include "Particle.h"

#include "VConfigurations.h"
#include "Configurations/Configurations.h"

#include "VFermiBreakUp.h"

namespace fermi {

  class FermiBreakUp : public VFermiBreakUp {
  public:
    FermiBreakUp();

    FermiBreakUp(std::unique_ptr<VConfigurations>&& configurations);

    ParticleVector BreakItUp(const Particle& nucleus) override final;

    ~FermiBreakUp() = default;

    static std::unique_ptr<VConfigurations> DefaultConfigurations();

  private:
    std::unique_ptr<VConfigurations> fermi_configurations_;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_
