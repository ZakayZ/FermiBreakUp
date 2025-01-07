//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_
#define FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_

#include <memory>
#include <map>

#include "Utilities/DataTypes.h"
#include "Utilities/Singleton.h"
#include "Fragments/Fragment.h"
#include "FragmentsStorage.h"

namespace fermi {

    using FragmentPool = Singleton<FragmentsStorage>;

} // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_
