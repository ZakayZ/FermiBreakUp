//
// Created by Artem Novikov on 21.02.2023.
//

#include "FermiBreakUp.h"
#include "DataTypes.h"
#include "PhaseDecay/FermiPhaseSpaceDecay.h"

ParticleSplit FermiBreakUp::BreakItUp(const FermiParticle& nucleus, bool cache) {
  /// CHECK that Excitation Energy > 0
  if (nucleus.GetExcitationEnergy() <= 0) {
    return {nucleus};
  }

  /// Total energy of nucleus in nucleus rest frame
  FermiFloat total_energy = nucleus.GetMomentum().m();

  /// Split the nucleus
  FermiConfigurations configurations(nucleus.GetMassNumber(), nucleus.GetChargeNumber(), total_energy, cache);
  if (!configurations.IsSplitPossible()) {
    return {nucleus};
  }

  return ConvertToParticles(nucleus, configurations.ChooseSplit());
}

ParticleSplit FermiBreakUp::ConvertToParticles(const FermiParticle& source_nucleus, const FragmentSplit& split) {
  ParticleSplit particle_split;
  particle_split.reserve(2 * split.size());

  std::vector<FermiFloat> split_masses;
  split_masses.reserve(split.size());
  for (auto fragment_ptr : split) {
    split_masses.push_back(fragment_ptr->GetTotalEnergy());
  }

  FermiPhaseSpaceDecay phase_sampler;
  std::vector<LorentzVector> particles_momentum = phase_sampler.CalculateDecay(source_nucleus.GetMomentum(), split_masses);

  Vector3 boost_vector = source_nucleus.GetMomentum().boostVector();

  /// Go back to the Lab Frame
  for (size_t fragment_idx = 0; fragment_idx < split.size(); ++fragment_idx) {
    ParticleVector fragment_particles = split[fragment_idx]->GetFragment(
        particles_momentum[fragment_idx].boost(boost_vector));

    particle_split.insert(particle_split.end(), std::make_move_iterator(fragment_particles.begin()),
              std::make_move_iterator(fragment_particles.end()));
  }

  return particle_split;
}
