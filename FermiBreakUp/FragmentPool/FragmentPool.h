//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FragmentPOOL_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FragmentPOOL_H_

#include <memory>
#include <map>

#include "Utilities/DataTypes.h"
#include "Utilities/Singleton.h"
#include "Fragments/Fragment.h"
#include "FragmentsStorage.h"

namespace fermi {

    using FragmentPool = Singleton<FragmentsStorage>;

} // namespace fermi

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FragmentPOOL_H_
