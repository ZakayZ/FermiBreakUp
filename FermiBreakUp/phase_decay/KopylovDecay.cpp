//
// Created by Artem Novikov on 21.02.2023.
//

#include <numeric>
#include <functional>
#include <CLHEP/Random/RandGamma.h>

#include "KopylovDecay.h"
#include "util/Randomizer.h"

using namespace fermi;

namespace {
  LorentzVector ChangeFrameOfReference(const LorentzVector& vec, const Vector3& boostVector) {
    auto copy = vec;
    copy.boost(boostVector);
    return copy;
  }
} // namespace

std::vector<LorentzVector> KopylovDecay::CalculateDecay(
  const LorentzVector& totalMomentum,
  const std::vector<FermiFloat>& fragmentsMass) const
{
  assert(fragmentsMass.size() > 0);

  std::vector<LorentzVector> result(fragmentsMass.size());

  if (fragmentsMass.size() == 1) {
    result[0] = totalMomentum;
    return result;
  }

  // 2 bodies case is faster
  if (fragmentsMass.size() == 2) {
    std::tie(result[0], result[1]) = TwoBodyDecay(totalMomentum.m(), fragmentsMass[0], fragmentsMass[1]);
    return result;
  }

  // N body case
  FermiFloat parentMass = totalMomentum.m();
  FermiFloat totalFragmentsMass = std::accumulate(fragmentsMass.begin(), fragmentsMass.end(), FermiFloat(0));
  FermiFloat mu = totalFragmentsMass;
  FermiFloat mass = parentMass;
  FermiFloat kineticEnergy = parentMass - totalFragmentsMass;
  assert(kineticEnergy > 0);

  auto momentumRestLab = LorentzVector(0, 0, 0, parentMass);
  for (size_t i = fragmentsMass.size() - 1; i > 0; --i) {
    mu -= fragmentsMass[i];
    kineticEnergy *= i > 1 ? BetaKopylov(i) : 0;
    auto restMass = mu + kineticEnergy;

    if (fragmentsMass[i] + restMass < mass) {
      throw std::runtime_error("FermiPhaseSpaceDecay::KopylovNBodyDecay: Error sampling fragments momenta!!");
    }
    auto [momentumFragmentsCm, momentumRestCm] = TwoBodyDecay(mass, fragmentsMass[i], restMass);

    // change framework
    const auto boostVector = momentumRestLab.boostVector();

    momentumRestLab = ChangeFrameOfReference(momentumRestCm, boostVector);
    auto momentumFragmentsLab = ChangeFrameOfReference(momentumFragmentsCm, boostVector);

    result[i] = momentumFragmentsLab;

    mass = restMass;
  }

  result[0] = std::move(momentumRestLab);

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
