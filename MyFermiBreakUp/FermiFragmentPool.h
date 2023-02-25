//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_

#include <map>

#include "DataTypes.h"
#include "FermiFragment.h"

/// Singleton of fragments wrapper class

class FermiFragmentPool {
 private:
  using RangeIterators = std::pair<std::multimap<NucleiData, const FermiFragment*>::const_iterator,
                                   std::multimap<NucleiData, const FermiFragment*>::const_iterator>;
 public:
  FermiFragmentPool();

  size_t Count(uint32_t mass_number, uint32_t charge_number) const;

  size_t Count(const NucleiData& nuclei) const;

  RangeIterators GetFragments(uint32_t mass_number, uint32_t charge_number) const;

  RangeIterators GetFragments(const NucleiData& nuclei) const;

 private:
  void AddFragment(const FermiFragment& fragment) const;

  static std::multimap<NucleiData, const FermiFragment*>* fragments_pool_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
