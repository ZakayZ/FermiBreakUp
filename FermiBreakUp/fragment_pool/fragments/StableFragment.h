//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_STABLEFRAGMENT_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_STABLEFRAGMENT_H

#include "Fragment.h"

namespace fbu {
  class StableFragment : public Fragment {
  public:
    using Fragment::Fragment;

    void AppendDecayFragments(const LorentzVector& momentum, std::vector<Particle>& fragments) const override;
  };
} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTS_STABLEFRAGMENT_H
