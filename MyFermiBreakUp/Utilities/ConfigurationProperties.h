//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_CONFIGURATIONPROPERTIES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_CONFIGURATIONPROPERTIES_H_

#include <vector>

#include "FermiSplit.h"

class ConfigurationProperties {
 public:
  static FermiFloat DecayProbability(const FragmentSplit& split, uint32_t atomic_weight, FermiFloat total_energy);

  static FermiFloat CoulombBarrier(const FragmentSplit& split);

  static FermiFloat CalculateSpinFactor(const FragmentSplit& split);

  static FermiFloat CalculateKineticEnergy(const FragmentSplit& split, FermiFloat total_energy);

  static FermiFloat CalculateMassFactor(const FragmentSplit& split);

  static FermiFloat CalculateConfigurationFactor(const FragmentSplit& split);

 private:
  static FermiFloat CalculateConstFactor(uint32_t atomic_weight, uint32_t fragments_count);

  static FermiFloat CalculateGammaFactor(uint32_t fragments_count);

  /// Kappa = V/V_0 it is used in calculation of Coulomb energy
  static const FermiFloat Kappa;

  /// Nuclear radius r0 (is a model parameter)
  static const FermiFloat r0;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_CONFIGURATIONPROPERTIES_H_
