//
// Created by Artem Novikov on 21.02.2023.
//

#include "FermiBreakUp.h"

#include "configurations/impl/Configurations.h"

using namespace fermi;

FermiBreakUp::FermiBreakUp() : configurations_(DefaultConfigurations()) {};

FermiBreakUp::FermiBreakUp(std::unique_ptr<VConfigurations>&& configurations)
  : configurations_(std::move(configurations))
{
}

ParticleVector FermiBreakUp::BreakItUp(const Particle& nucleus) {
  // CHECK that Excitation Energy > 0
  if (nucleus.GetExcitationEnergy() < 0) {
    return {nucleus};
  }

  // Total energy of nucleus in nucleus rest frame
  auto totalEnergy = nucleus.GetMomentum().m();

  // Split the nucleus
  auto fragmentSplit = configurations_->GenerateSplits(nucleus.GetNucleiData(), totalEnergy).ChooseSplit();
  if (!fragmentSplit.has_value()) {
    return {nucleus};
  }

  return ConvertToParticles(nucleus, fragmentSplit.value());
}

std::unique_ptr<VConfigurations> FermiBreakUp::DefaultConfigurations() {
  return std::make_unique<Configurations>();
}
