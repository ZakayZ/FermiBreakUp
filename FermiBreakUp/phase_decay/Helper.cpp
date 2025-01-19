//
// Created by Artem Novikov on 21.02.2023.
//

#include "util/Randomizer.h"
#include "util/Logger.h"

#include "Helper.h"

using namespace fermi;

FermiFloat fermi::TwoBodyMomentum2(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2) {
  ASSERT_MSG(totalEnergy > mass1 + mass2, "totalEnergy is less than fragments mass");

  return (totalEnergy + mass1 + mass2)
      * (totalEnergy + mass1 - mass2)
      * (totalEnergy - mass1 + mass2)
      * (totalEnergy - mass1 - mass2)
      / (4.0 * std::pow(totalEnergy, 2));
}

FermiFloat fermi::TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2) {
  return std::sqrt(TwoBodyMomentum2(totalEnergy, mass1, mass2));
}

std::pair<LorentzVector, LorentzVector> fermi::TwoBodyDecay(
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
