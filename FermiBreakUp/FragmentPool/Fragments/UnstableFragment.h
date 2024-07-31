//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFragment_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFragment_H_

#include <vector>

#include "Fragment.h"

namespace fermi {

  class UnstableFragment : public Fragment {
  public:
    using Fragment::Fragment;

    UnstableFragment() = delete;

    UnstableFragment(const UnstableFragment&) = delete;

    const UnstableFragment& operator=(const UnstableFragment&) = delete;

    ParticleVector GetFragments(const LorentzVector& momentum) const override;

  protected:
    void Build(const std::vector<NucleiData>& decay_data);

    void Build(std::vector<NucleiData>&& decay_data);

    void FillMasses();

  private:
    std::vector<NucleiData> decay_data_;
    std::vector<FermiFloat> masses_;
  };

}  // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTS_UNSTABLEFragment_H_
