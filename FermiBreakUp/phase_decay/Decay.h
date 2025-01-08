//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_

#include "VDecay.h"

namespace fermi {

  class Decay : public VDecay {
  public:
    std::vector<LorentzVector> CalculateDecay(const LorentzVector& momentum,
                                              const std::vector<FermiFloat>& fragmentsMass) const override;

  private:
    static std::vector<FermiFloat> CalculateVirtualMasses(const std::vector<FermiFloat>& masses, FermiFloat energy);

    // modifies vector for a optimization purposes
    static FermiFloat CalculateMomentumMagnitudes(std::vector<FermiFloat>& daughterMomentum,
                                          const std::vector<FermiFloat>& masses,
                                          const std::vector<FermiFloat>& virtualMasses);

    static FermiFloat CalculateMaxWeight(const std::vector<FermiFloat>& masses, FermiFloat maxEnergy);
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESDECAYH_
