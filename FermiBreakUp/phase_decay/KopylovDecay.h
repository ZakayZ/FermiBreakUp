//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESKOPYLOVDECAYH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESKOPYLOVDECAYH_

#include "VDecay.h"

namespace fermi {

  class KopylovDecay : public VDecay{
  public:
    std::vector<LorentzVector> CalculateDecay(const LorentzVector& momentum,
                                              const std::vector<FermiFloat>& fragmentsMass) const override;

  private:
    static FermiFloat BetaKopylov(size_t k);
  };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESKOPYLOVDECAYH_
