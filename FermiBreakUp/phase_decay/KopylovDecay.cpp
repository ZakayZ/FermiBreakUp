//
// Created by Artem Novikov on 21.02.2023.
//

#include <numeric>
#include <functional>
#include <CLHEP/Random/RandGamma.h>

#include "KopylovDecay.h"
#include "utilities/Randomizer.h"

using namespace fermi;

std::vector<LorentzVector> KopylovDecay::CalculateDecay(const LorentzVector& momentum,
                                                        const std::vector<FermiFloat>& fragmentsMass) const {
  std::vector<LorentzVector> result(fragmentsMass.size());

  FermiFloat parentMass = momentum.m();
  FermiFloat totalFragmentsMass = std::accumulate(fragmentsMass.begin(), fragmentsMass.end(), FermiFloat(0));
  FermiFloat mu = totalFragmentsMass;
  FermiFloat mass = parentMass;
  FermiFloat kineticEnergy = parentMass - totalFragmentsMass;

  auto momentumRestLab = LorentzVector(0, 0, 0, parentMass);
  for (size_t i = fragmentsMass.size() - 1; i > 0; --i) {
    mu -= fragmentsMass[i];
    kineticEnergy *= i > 1 ? BetaKopylov(i) : 0;
    auto restMass = mu + kineticEnergy;

    auto momentumMagnitudeFragmentsCm = TwoBodyMomentum(mass, fragmentsMass[i], restMass);
    if (momentumMagnitudeFragmentsCm < 0) {
      throw std::runtime_error("FermiPhaseSpaceDecay::KopylovNBodyDecay: Error sampling fragments momenta!!");
    }

    ParticleMomentum randomMomentum = Randomizer::IsotropicVector(momentumMagnitudeFragmentsCm);
    auto momentumFragmentsCm = LorentzVector(randomMomentum,
                                               std::sqrt(randomMomentum.mag2() + std::pow(fragmentsMass[i], 2)));
    auto momentumRestCm = LorentzVector(-randomMomentum, std::sqrt(randomMomentum.mag2() + std::pow(restMass, 2)));

    // change framework
    Vector3 boostVector = momentumRestLab.boostVector();

    momentumRestLab = LorentzVector(momentumRestCm).boost(boostVector);
    auto momentumFragmentsLab = LorentzVector(momentumFragmentsCm).boost(boostVector);

    result[i] = momentumFragmentsLab;

    mass = restMass;
  }

  result[0] = momentumRestLab;

  return result;
}

FermiFloat KopylovDecay::BetaKopylov(size_t k) {
  // Notice that alpha > beta always
  static const FermiFloat beta = 1.5;
  FermiFloat alpha = 1.5 * static_cast<FermiFloat>(k - 1);
  FermiFloat y1 = CLHEP::RandGamma::shoot(alpha, 1);
  FermiFloat y2 = CLHEP::RandGamma::shoot(beta, 1);

  return y1 / (y1 + y2);
}
