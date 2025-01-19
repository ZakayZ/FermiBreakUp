//
// Created by Artem Novikov on 21.02.2023.
//

#include <exception>
#include <numeric>
#include <functional>

#include <CLHEP/Random/RandGamma.h>

#include "util/Randomizer.h"
#include "util/Logger.h"

#include "Helper.h"
#include "KopylovDecay.h"

using namespace fermi;

namespace {
  LorentzVector ChangeFrameOfReference(const LorentzVector& vec, const Vector3& boostVector) {
    auto copy = vec;
    copy.boost(boostVector);
    return copy;
  }

  FermiFloat BetaKopylov(size_t k) {
    constexpr FermiFloat beta = 1.5;

    // Notice that alpha > beta always
    const FermiFloat alpha = 1.5 * static_cast<FermiFloat>(k - 1);
    const FermiFloat y1 = CLHEP::RandGamma::shoot(alpha, 1);
    const FermiFloat y2 = CLHEP::RandGamma::shoot(beta, 1);

    return y1 / (y1 + y2);
  }
} // namespace

std::vector<LorentzVector> KopylovDecay::CalculateDecay(
  const LorentzVector& totalMomentum,
  const std::vector<FermiFloat>& fragmentsMass) const
{
  LOG_TRACE("Kopylov Decay called");
  ASSERT_MSG(fragmentsMass.size() > 0, "Kopylov Decay called for empty split");

  std::vector<LorentzVector> result(fragmentsMass.size());

  if (fragmentsMass.size() == 1) {
    LOG_DEBUG("No decay is needed, only one fragment");
    result[0] = totalMomentum;
    return result;
  }

  // 2 bodies case is faster
  if (fragmentsMass.size() == 2) {
    LOG_DEBUG("Decay for 2 fragments");
    std::tie(result[0], result[1]) = TwoBodyDecay(totalMomentum.m(), fragmentsMass[0], fragmentsMass[1]);
    return result;
  }

  // N body case
  LOG_DEBUG("Decay for N fragments");
  auto const parentMass = totalMomentum.m();
  auto const totalFragmentsMass = std::accumulate(fragmentsMass.begin(), fragmentsMass.end(), 0.);

  auto mu = totalFragmentsMass;
  auto mass = parentMass;
  auto kineticEnergy = parentMass - totalFragmentsMass;
  ASSERT_MSG(kineticEnergy >= 0.,
             "Kopylov Decay started for impossible split: fragments mass is too large");

  auto momentumRestLab = LorentzVector(0, 0, 0, parentMass);
  for (size_t i = fragmentsMass.size() - 1; i > 0; --i) {
    mu -= fragmentsMass[i];
    kineticEnergy *= i > 1 ? BetaKopylov(i) : 0.;
    const auto restMass = mu + kineticEnergy;

    ASSERT_MSG(fragmentsMass[i] + restMass <= mass,
               "Kopylov Decay: something went wrong, fragments mass is greater than the whole");
    auto [momentumFragmentsCm, momentumRestCm] = TwoBodyDecay(mass, fragmentsMass[i], restMass);

    const auto boostVector = momentumRestLab.boostVector();
    momentumRestLab = ChangeFrameOfReference(momentumRestCm, boostVector);
    const auto momentumFragmentsLab = ChangeFrameOfReference(momentumFragmentsCm, boostVector);

    result[i] = momentumFragmentsLab;

    mass = restMass;
  }

  result[0] = std::move(momentumRestLab);

  return result;
}
