//
// Created by Artem Novikov on 21.05.2023.
//

#include "VFermiBreakUp.h"
#include "phase_decay/FermiPhaseSpaceDecay.h"

using namespace fermi;

ParticleVector VFermiBreakUp::ConvertToParticles(const Particle& sourceNucleus, const FragmentVector& split) {
  ParticleVector particleSplit;
  particleSplit.reserve(2 * split.size());

  std::vector<FermiFloat> splitMasses;
  splitMasses.reserve(split.size());
  for (auto fragmentPtr : split) {
    splitMasses.push_back(fragmentPtr->GetTotalEnergy());
  }

  FermiPhaseSpaceDecay phaseSampler;
  auto particlesMomentum = phaseSampler.CalculateDecay(sourceNucleus.GetMomentum(), splitMasses);

  auto boostVector = sourceNucleus.GetMomentum().boostVector();

  // Go back to the Lab Frame
  for (size_t fragmentIdx = 0; fragmentIdx < split.size(); ++fragmentIdx) {
    ParticleVector fragmentParticles = split[fragmentIdx]->GetFragments(
        particlesMomentum[fragmentIdx].boost(boostVector));

    particleSplit.insert(particleSplit.end(), std::make_move_iterator(fragmentParticles.begin()),
                          std::make_move_iterator(fragmentParticles.end()));
  }

  return particleSplit;
}