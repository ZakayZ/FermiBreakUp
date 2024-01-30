//
// Created by Artem Novikov on 25.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTBUILDER_H_

#include "VPoolBuilder.h"
#include "../Fragments/FermiFragment.h"

namespace pool {

class DefaultBuilder : public VPoolBuilder {
 public:
  void Build(FermiFragmentPool::Storage& map) const override;
};

} // namespace pool

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FRAGMENTPOOL_BUILDER_DEFAULTBUILDER_H_
