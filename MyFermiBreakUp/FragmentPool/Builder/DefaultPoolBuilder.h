//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTPOOLBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTPOOLBUILDER_H_

#include "VPoolBuilder.h"
#include "../Fragments/FermiFragment.h"

class DefaultPoolBuilder : public VPoolBuilder {
 public:
  void Build(FermiFragmentPool::Map& map) const override;

 private:
  void AddFragment(FermiFragmentPool::Map& map, const FermiFragment& fragment) const;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTPOOLBUILDER_H_
