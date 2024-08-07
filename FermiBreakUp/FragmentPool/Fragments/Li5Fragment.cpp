//
// Created by Artem Novikov on 18.02.2023.
//

#include "Li5Fragment.h"

using namespace fermi;

Li5Fragment::Li5Fragment(MassNumber mass_number,
                                   ChargeNumber charge_number,
                                   int polarization,
                                   FermiFloat excitation_energy)
    : UnstableFragment(mass_number, charge_number, polarization, excitation_energy) {
  // Li5 ----> alpha + proton

  Build({NucleiData{4_m, 2_c},
         NucleiData{1_m, 1_c}});
}
