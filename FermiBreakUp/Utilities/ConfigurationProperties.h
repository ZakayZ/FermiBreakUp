//
// Created by Artem Novikov on 19.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESCONFIGURATIONPROPERTIESH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESCONFIGURATIONPROPERTIESH_

#include <vector>

#include "Split.h"

namespace fermi {

  class ConfigurationProperties {
  public:
    static FermiFloat DecayProbability(const FragmentVector& split, uint32_t atomicWeight, FermiFloat totalEnergy);

    static FermiFloat CoulombBarrier(const FragmentVector& split);

    static FermiFloat CalculateSpinFactor(const FragmentVector& split);

    static FermiFloat CalculateKineticEnergy(const FragmentVector& split, FermiFloat totalEnergy);

    static FermiFloat CalculateMassFactor(const FragmentVector& split);

    static FermiFloat CalculateConfigurationFactor(const FragmentVector& split);

  private:
    static FermiFloat CalculateConstFactor(uint32_t atomicWeight, size_t fragmentsCount);

    static FermiFloat CalculateGammaFactor(size_t fragmentsCount);

    // Kappa = V/V_0 it is used in calculation of Coulomb energy
    static const FermiFloat KAPPA;

    // Nuclear radius r0 (is a model parameter)
    static const FermiFloat R0;
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESCONFIGURATIONPROPERTIESH_
