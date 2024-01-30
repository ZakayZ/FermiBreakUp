//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_

#include <memory>
#include <map>

#include "Utilities/DataTypes.h"
#include "Fragments/FermiFragment.h"
#include "FragmentsStorage.h"

namespace pool {

class VPoolBuilder;

class FermiFragmentPool {
 public:
  using Storage = FragmentsStorage;
  using RangeIterators = Storage::RangeIterators;

  FermiFragmentPool();

  FermiFragmentPool(const VPoolBuilder& builder);

  [[nodiscard]] size_t Count(MassNumber mass_number, ChargeNumber charge_number) const;

  [[nodiscard]] size_t Count(NucleiData nuclei) const;

  [[nodiscard]] RangeIterators GetFragments(MassNumber mass_number, ChargeNumber charge_number) const;

  [[nodiscard]] RangeIterators GetFragments(NucleiData nuclei) const;

 private:
  void Build(const VPoolBuilder& builder);

  static std::unique_ptr<Storage> fragments_pool_;
};

} // namespace pool

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIFRAGMENTPOOL_H_
