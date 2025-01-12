//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_

#include <vector>
#include <optional>
#include "utilities/DataTypes.h"

namespace fermi {

  FermiFloat TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  std::pair<LorentzVector, LorentzVector> TwoBodyDecay(
    FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

  class VDecay {
  public:
    VDecay() = default;

    virtual std::vector<LorentzVector> CalculateDecay(
      const LorentzVector& totalMomentum,
      const std::vector<FermiFloat>& fragmentsMass) const = 0;

    virtual ~VDecay() = default;
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_
