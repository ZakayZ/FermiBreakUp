//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_STABLEFragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_STABLEFragment_H_

#include "Fragment.h"

namespace fermi {

  class StableFragment : public Fragment {
  public:
    using Fragment::Fragment;

    StableFragment() = delete;

    StableFragment(const StableFragment&) = delete;

    StableFragment& operator=(const StableFragment&) = delete;

    ParticleVector GetFragments(const LorentzVector& momentum) const override;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_STABLEFragment_H_
