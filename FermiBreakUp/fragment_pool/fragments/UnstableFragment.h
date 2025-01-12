//
// Created by Artem Novikov on 17.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSUNSTABLEFragmentH_
#define FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSUNSTABLEFragmentH_

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
    void Build(const std::vector<NucleiData>& decayData);

    void Build(std::vector<NucleiData>&& decayData);

    void FillMasses();

  private:
    std::vector<NucleiData> decayData_;
    std::vector<FermiFloat> masses_;
  };

}  // namespace fermi

#endif // FERMIBREAKUPMYFERMIBREAKUPFRAGMENTSUNSTABLEFragmentH_
