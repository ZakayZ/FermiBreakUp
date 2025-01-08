//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_
#define FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_

#include <vector>
#include "utilities/DataTypes.h"

namespace fermi {

    class VDecay {
    public:
    VDecay() = default;

    virtual std::vector<LorentzVector> CalculateDecay(const LorentzVector& momentum,
                                                const std::vector<FermiFloat>& fragmentsMass) const = 0;

    virtual ~VDecay() = 0;

    protected:
    static FermiFloat TwoBodyMomentum(FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);

    static std::pair<LorentzVector, LorentzVector> TwoBodyDecay(
        FermiFloat totalEnergy, FermiFloat mass1, FermiFloat mass2);
    };

}  // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPUTILITIESVDECAYH_
