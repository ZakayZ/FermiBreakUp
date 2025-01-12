//
// Created by Artem Novikov on 17.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPFRAGMENTPOOLDATASOURCEDEFAULTPOOLSOURCEH_
#define HANDLERMYFERMIBREAKUPFRAGMENTPOOLDATASOURCEDEFAULTPOOLSOURCEH_

#include <vector>

#include "fragment_pool/fragments/Fragment.h"

namespace fermi {

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

} // namespace fermi

#endif // HANDLERMYFERMIBREAKUPFRAGMENTPOOLDATASOURCEDEFAULTPOOLSOURCEH_
