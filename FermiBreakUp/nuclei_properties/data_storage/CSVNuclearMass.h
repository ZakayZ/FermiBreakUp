//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_CSVNUCLEARMASS_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_CSVNUCLEARMASS_H

#include <unordered_map>

#include "FermiBreakUp/util/DataTypes.h"

namespace fbu {
  class CSVNuclearMass : private std::unordered_map<NucleiData, FermiFloat> {
  private:
    using Container = std::unordered_map<NucleiData, FermiFloat>;

  public:
    CSVNuclearMass(
      const FermiStr& csvFilename,
      const FermiStr& massNumberName = "A",
      const FermiStr& chargeNumberName = "Z",
      const FermiStr& massName = "mass"
    );

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };
} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_CSVNUCLEARMASS_H
