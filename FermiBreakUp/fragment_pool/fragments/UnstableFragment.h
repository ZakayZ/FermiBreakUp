//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_UNSTABLEFRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_UNSTABLEFRAGMENT_H

#include "Fragment.h"

namespace fermi {

  class UnstableFragment : public Fragment {
  public:
    UnstableFragment(
      AtomicMass atomicMass,
      ChargeNumber chargeNumber,
      FermiInt polarization,
      FermiFloat excitationEnergy,
      std::vector<NucleiData>&& decayData);

    void AppendDecayFragments(
      const LorentzVector& momentum,
      std::vector<Particle>& particles) const override;

  private:
    std::vector<NucleiData> decayData_;
    std::vector<FermiFloat> masses_;
  };

  #define AddUnstaleFragment(NAME, FRAGMENTS) \
    inline UnstableFragment NAME(             \
        AtomicMass atomicMass,                \
        ChargeNumber chargeNumber,            \
        FermiInt polarization,                \
        FermiFloat excitationEnergy)          \
    {                                         \
      return UnstableFragment(                \
        atomicMass,                           \
        chargeNumber,                         \
        polarization,                         \
        excitationEnergy,                     \
        FRAGMENTS                             \
      );                                      \
    }

  // He5 ----> alpha + neutron
  AddUnstaleFragment(He5Fragment, std::vector<NucleiData>({
    NucleiData{4_m, 2_c},
    NucleiData{1_m, 0_c},
  }));

  // B9 ----> alpha + alpha + proton
  AddUnstaleFragment(B9Fragment, std::vector<NucleiData>({
    NucleiData{4_m, 2_c},
    NucleiData{4_m, 2_c},
    NucleiData{1_m, 1_c},
  }));

  // Be8 ----> alpha + alpha
  AddUnstaleFragment(Be8Fragment, std::vector<NucleiData>({
    NucleiData{4_m, 2_c},
    NucleiData{4_m, 2_c},
  }));

  // Li5 ----> alpha + proton
  AddUnstaleFragment(Li5Fragment, std::vector<NucleiData>({
    NucleiData{4_m, 2_c},
    NucleiData{1_m, 1_c},
  }));

  #undef AddUnstaleFragment

} // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_UNSTABLEFRAGMENT_H
