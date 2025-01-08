//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_
#define HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_

#include <map>

#include "utilities/DataTypes.h"

namespace properties {

  class CSVNuclearMass {
  private:
    using Container = std::map<NucleiData, FermiFloat>;

  public:
    CSVNuclearMass(
      const std::string& csvFilename,
      const std::string& massNumberName = "A",
      const std::string& chargeNumberName = "Z",
      const std::string& massName = "mass"
    );

    ~CSVNuclearMass() = default;

    Container::iterator begin() { return masses_.begin(); }

    [[nodiscard]] Container::const_iterator begin() const { return masses_.begin(); }

    [[nodiscard]] Container::const_iterator cbegin() const { return masses_.cbegin(); }

    Container::iterator end() { return masses_.end(); }

    [[nodiscard]] Container::const_iterator end() const { return masses_.end(); }

    [[nodiscard]] Container::const_iterator cend() const { return masses_.cend(); }

  private:
    Container masses_;
  };

} // namespace properties

#endif //HANDLERMYFERMIBREAKUPUTILITIESNUCLEIPROPERTIESDATASTORAGECSVNUCLEARMASSH_
