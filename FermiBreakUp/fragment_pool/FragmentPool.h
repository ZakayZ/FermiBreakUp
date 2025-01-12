//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H
#define FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H

#include <memory>
#include <map>

#include "utilities/DataTypes.h"
#include "utilities/Singleton.h"
#include "fragments/Fragment.h"
#include "FragmentsStorage.h"

namespace fermi {

    using FragmentPool = Singleton<FragmentsStorage>;

} // namespace fermi

#endif // FERMIBREAKUP_FRAGMENT_POOL_FRAGMENTPOOL_H
