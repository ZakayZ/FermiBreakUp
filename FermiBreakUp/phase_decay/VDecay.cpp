//
// Created by Artem Novikov on 21.02.2023.
//

#include "VDecay.h"
#include "utilities/Randomizer.h"

FermiFloat fermi::TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2) {
  assert(totalEnergy > mass1 + mass2);

  FermiFloat sqProbability =
      (totalEnergy + mass1 + mass2)
      * (totalEnergy + mass1 - mass2)
      * (totalEnergy - mass1 + mass2)
      * (totalEnergy - mass1 - mass2)
      / (4.0 * std::pow(totalEnergy, 2));

  return std::sqrt(sqProbability);
}

std::pair<LorentzVector, LorentzVector> fermi::TwoBodyDecay(FermiFloat totalEnergy,
                                                            FermiFloat mass1,
                                                            FermiFloat mass2)
{
  auto psqr = TwoBodyMomentum(totalEnergy, mass1, mass2);
  ParticleMomentum momentum = Randomizer::IsotropicVector(std::sqrt(psqr));

  return {
    LorentzVector(momentum, std::sqrt(psqr + std::pow(mass1, 2))),
    LorentzVector(-momentum, std::sqrt(psqr + std::pow(mass2, 2))),
  };
}