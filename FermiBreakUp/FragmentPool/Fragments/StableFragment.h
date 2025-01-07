//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSSTABLEFragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSSTABLEFragmentH_

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

#endif //FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSSTABLEFragmentH_
