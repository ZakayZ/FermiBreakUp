//
// Created by Artem Novikov on 07.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_

#include <CLHEP/Vector/LorentzVector.h>

using FermiInt = int;

using FermiFloat = double;

using LorentzVector = CLHEP::HepLorentzVector;

using Vector3 = CLHEP::Hep3Vector;

using ParticleMomentum = Vector3;

struct NucleiData {
  uint32_t mass_number;
  uint32_t charge_number;

  bool operator<(const NucleiData& other) const {
    return mass_number < other.mass_number
        || mass_number == other.mass_number && charge_number < other.charge_number;
  }
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_DATATYPES_H_
