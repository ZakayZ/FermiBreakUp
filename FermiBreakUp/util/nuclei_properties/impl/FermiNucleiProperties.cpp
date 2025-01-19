//
// Created by Artem Novikov on 09.03.2023.
//

#include "util/Logger.h"
#include "util/nuclei_properties/data_storage/DefaultNuclearMass.h"

#include "FermiNucleiProperties.h"

using namespace fermi;

FermiNucleiProperties::FermiNucleiProperties()
  : FermiNucleiProperties(DefaultNuclearMass())
{
}

FermiFloat FermiNucleiProperties::GetNuclearMass(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  auto it = nucleiMass_.find(NucleiData{atomicMass, chargeNumber});
  if (it != nucleiMass_.end()) {
    return it->second;
  }

  LOG_DEBUG("Unknown particle: A = " << atomicMass << ", Z = " << chargeNumber);
  return EstimateNuclearMass(atomicMass, chargeNumber);
}

bool FermiNucleiProperties::IsStable(AtomicMass atomicMass, ChargeNumber chargeNumber) const {
  if (atomicMass < 1_m || chargeNumber < 0_c || FermiUInt(chargeNumber) > FermiUInt(atomicMass)) {
    LOG_DEBUG("Unsupported values for A = " << atomicMass << " and Z = " << chargeNumber);
    return false;
  }

  return nucleiMass_.find(NucleiData{atomicMass, chargeNumber}) != nucleiMass_.end();
}

void FermiNucleiProperties::AddMass(AtomicMass atomicMass, ChargeNumber chargeNumber, FermiFloat mass) {
  return AddMass(NucleiData{atomicMass, chargeNumber}, mass);
}

void FermiNucleiProperties::AddMass(NucleiData nucleiData, FermiFloat mass) {
  nucleiMass_[nucleiData] = mass;
}
