//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGEDEFAULTNUCLEARMASSH_
#define HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGEDEFAULTNUCLEARMASSH_

#include <vector>

#include "utilities/DataTypes.h"

namespace properties {

  class DefaultNuclearMass : private std::vector<std::pair<const NucleiData, FermiFloat>> {
  private:
    using Container = std::vector<std::pair<const NucleiData, FermiFloat>>;

  public:
    DefaultNuclearMass();

    ~DefaultNuclearMass() = default;

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };

} // properties

#endif // HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGEDEFAULTNUCLEARMASSH_
