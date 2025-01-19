//
// Created by Artem Novikov on 18.02.2024.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_DEFAULTNUCLEARMASS_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_DEFAULTNUCLEARMASS_H

#include <vector>

#include "util/DataTypes.h"

namespace fermi {

  class DefaultNuclearMass : private std::vector<std::pair<const NucleiData, FermiFloat>> {
  private:
    using Container = std::vector<std::pair<const NucleiData, FermiFloat>>;

  public:
    DefaultNuclearMass();

    using Container::iterator;
    using Container::const_iterator;
    using Container::begin;
    using Container::cbegin;
    using Container::end;
    using Container::cend;
  };

} // fermi

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_DATA_STORAGE_DEFAULTNUCLEARMASS_H
