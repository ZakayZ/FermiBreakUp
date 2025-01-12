//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_
#define HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_

#include <map>

#include "utilities/DataTypes.h"

namespace properties {

  class CSVNuclearMass : private std::map<NucleiData, FermiFloat> {
  private:
    using Container = std::map<NucleiData, FermiFloat>;

  public:
    CSVNuclearMass(
      const std::string& csvFilename,
      const std::string& massNumberName = "A",
      const std::string& chargeNumberName = "Z",
      const std::string& massName = "mass"
    );

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };

} // namespace properties

#endif // HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_
