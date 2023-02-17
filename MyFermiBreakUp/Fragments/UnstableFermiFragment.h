//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFERMIFRAGMENT_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFERMIFRAGMENT_H_

#include <vector>
#include "FermiFragment.h"

class UnstableFermiFragment : public FermiFragment {
 public:
  using FermiFragment::FermiFragment;

  UnstableFermiFragment() = delete;

  UnstableFermiFragment(const UnstableFermiFragment&) = delete;

  const UnstableFermiFragment& operator=(const UnstableFermiFragment&) = delete;

  FragmentVector GetFragment(const LorentzVector& momentum) const override;

 private:
  template <typename... Args>
  using Container = std::vector<Args...>;

  struct DecayFragments {
    uint32_t mass_number;
    uint32_t charge_number;
    FermiFloat mass;
  };

  Container<DecayFragments> decay_data_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFERMIFRAGMENT_H_
