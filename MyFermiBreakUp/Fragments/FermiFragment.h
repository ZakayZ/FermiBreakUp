//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_FERMIFRAGMENT_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_FERMIFRAGMENT_H_

#include <vector>

#include "DataTypes.h"

class FermiFragment {
 public:
  FermiFragment(uint32_t mass_number, uint32_t proton_number, int polarization, FermiFloat excitation_energy);

  FermiFragment(const FermiFragment&) = delete;

  FermiFragment& operator=(const FermiFragment&) = delete;

  virtual FragmentVector GetFragment(const LorentzVector& momentum) const = 0;

  uint32_t GetA() const;

  uint32_t GetMassNumber() const;

  uint32_t GetZ() const;

  uint32_t GetProtonNumber() const;

  int32_t GetPolarization() const;

  FermiFloat GetExcitationEnergy() const;

  FermiFloat GetFragmentMass() const;

  FermiFloat GetTotalEnergy() const;

  virtual ~FermiFragment() = 0;

 protected:
  uint32_t mass_number_; /// A
  uint32_t proton_number_; /// Z
  int32_t polarization;
  FermiFloat excitation_energy_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_FERMIFRAGMENT_H_
