//
// Created by Artem Novikov on 21.02.2023.
//

#include "VDecay.h"
#include "Utilities/Randomizer.h"

using namespace fermi;

VDecay::~VDecay() = default;

FermiFloat VDecay::TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2) {
  FermiFloat sqProbability =
      (totalEnergy + mass1 + mass2) * (totalEnergy + mass1 - mass2) * (totalEnergy - mass1 + mass2)
          * (totalEnergy - mass1 - mass2) / (4.0 * std::pow(totalEnergy, 2));

  if (sqProbability <= 0) { return -1; }

  return std::sqrt(sqProbability);
}

std::pair<LorentzVector, LorentzVector> VDecay::TwoBodyDecay(FermiFloat totalEnergy,
                                                             FermiFloat mass1,
                                                             FermiFloat mass2) {
  auto psqr = TwoBodyMomentum(totalEnergy, mass1, mass2);
  ParticleMomentum momentum = Randomizer::IsotropicVector(std::sqrt(psqr));

  std::pair<LorentzVector, LorentzVector> momentum4 = {LorentzVector(momentum, std::sqrt(psqr + std::pow(mass1, 2))),
                                                       LorentzVector(-momentum, std::sqrt(psqr + std::pow(mass2, 2)))};

  return momentum4;
}