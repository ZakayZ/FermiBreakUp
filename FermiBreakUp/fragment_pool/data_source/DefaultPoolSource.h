//
// Created by Artem Novikov on 17.02.2024.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_DATA_SOURCE_DEFAULTPOOLSOURCE_H
#define FERMIBREAKUP_FRAGMENT_POOL_DATA_SOURCE_DEFAULTPOOLSOURCE_H

#include <vector>

#include "FermiBreakUp/fragment_pool/fragments/Fragment.h"

namespace fbu {
  class DefaultPoolSource : private std::vector<const Fragment*> {
  private:
    using Container = std::vector<const Fragment*>;

  public:
    DefaultPoolSource();

    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };
} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_DATA_SOURCE_DEFAULTPOOLSOURCE_H
