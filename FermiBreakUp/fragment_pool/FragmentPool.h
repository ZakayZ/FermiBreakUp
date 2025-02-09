//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H

#include "FermiBreakUp/fragment_pool/fragments/Fragment.h"
#include "FermiBreakUp/util/DataTypes.h"
#include "FermiBreakUp/util/Singleton.h"

#include "FragmentsStorage.h"

namespace fbu {
  using FragmentPool = Singleton<FragmentsStorage>;
} // namespace fbu

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H
