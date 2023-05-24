//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_

#include <map>

#include "Utilities/DataTypes.h"
#include "Fragments/FermiFragment.h"

/// Singleton of fragments wrapper class

class FermiFragmentPool {
 private:
  using RangeIterators = std::pair<std::multimap<NucleiData, const FermiFragment*>::const_iterator,
                                   std::multimap<NucleiData, const FermiFragment*>::const_iterator>;
 public:
  FermiFragmentPool();

  size_t Count(MassNumber mass_number, ChargeNumber charge_number) const;

  size_t Count(NucleiData nuclei) const;

  RangeIterators GetFragments(MassNumber mass_number, ChargeNumber charge_number) const;

  RangeIterators GetFragments(NucleiData nuclei) const;

 private:
  void AddFragment(const FermiFragment& fragment) const;

  static std::multimap<NucleiData, const FermiFragment*>* fragments_pool_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
