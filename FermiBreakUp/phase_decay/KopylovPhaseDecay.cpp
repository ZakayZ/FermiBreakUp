//
// Created by Artem Novikov on 21.02.2023.
//

#include <exception>
#include <numeric>
#include <functional>

#include <CLHEP/Random/RandGamma.h>

#include "FermiBreakUp/util/Randomizer.h"
#include "FermiBreakUp/util/Logger.h"

#include "KopylovPhaseDecay.h"

using namespace fbu;

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

  FermiFloat TwoBodyMomentum2(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2) {
    FERMI_ASSERT_MSG(totalEnergy > mass1 + mass2, "totalEnergy is less than fragments mass");

    return (totalEnergy + mass1 + mass2)
        * (totalEnergy + mass1 - mass2)
        * (totalEnergy - mass1 + mass2)
        * (totalEnergy - mass1 - mass2)
        / (4.0 * std::pow(totalEnergy, 2));
  }

  std::pair<LorentzVector, LorentzVector> TwoBodyDecay(
    FermiFloat totalEnergy,
    FermiFloat mass1,
    FermiFloat mass2)
  {
    const auto mag2 = TwoBodyMomentum2(totalEnergy, mass1, mass2);
    const auto momentum = Randomizer::IsotropicVector(std::sqrt(mag2));

    return {
      LorentzVector(momentum, std::sqrt(mag2 + std::pow(mass1, 2))),
      LorentzVector(-momentum, std::sqrt(mag2 + std::pow(mass2, 2))),
    };
  }

} // namespace

std::vector<LorentzVector> KopylovPhaseDecay::CalculateDecay(
  const LorentzVector& totalMomentum,
  const std::vector<FermiFloat>& fragmentsMass) const
{
  FERMI_LOG_TRACE("Kopylov Decay called");
  FERMI_ASSERT_MSG(fragmentsMass.size() > 0, "Kopylov Decay called for empty split");

  std::vector<LorentzVector> result(fragmentsMass.size());

  if (fragmentsMass.size() == 1) {
    FERMI_LOG_DEBUG("No decay is needed, only one fragment");
    result[0] = totalMomentum;
    return result;
  }

  // 2 bodies case is faster
  if (fragmentsMass.size() == 2) {
    FERMI_LOG_DEBUG("Decay for 2 fragments");
    std::tie(result[0], result[1]) = TwoBodyDecay(totalMomentum.m(), fragmentsMass[0], fragmentsMass[1]);
    return result;
  }

  // N body case
  FERMI_LOG_DEBUG("Decay for N fragments");
  auto const parentMass = totalMomentum.m();
  auto const totalFragmentsMass = std::accumulate(fragmentsMass.begin(), fragmentsMass.end(), 0.);

  auto mu = totalFragmentsMass;
  auto mass = parentMass;
  auto kineticEnergy = parentMass - totalFragmentsMass;
  FERMI_ASSERT_MSG(kineticEnergy >= 0.,
             "Kopylov Decay started for impossible split: fragments mass is too large");

  auto momentumRestLab = LorentzVector(0, 0, 0, parentMass);
  for (size_t i = fragmentsMass.size() - 1; i > 0; --i) {
    mu -= fragmentsMass[i];
    kineticEnergy *= i > 1 ? BetaKopylov(i) : 0.;
    const auto restMass = mu + kineticEnergy;

    FERMI_ASSERT_MSG(fragmentsMass[i] + restMass <= mass,
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
