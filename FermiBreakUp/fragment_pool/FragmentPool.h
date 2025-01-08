//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_
#define FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_

#include <memory>
#include <map>

#include "utilities/DataTypes.h"
#include "utilities/Singleton.h"
#include "fragments/Fragment.h"
#include "FragmentsStorage.h"

namespace fermi {

    using fragment_pool = Singleton<FragmentsStorage>;

} // namespace fermi

#endif //FERMIBREAKUPMYFERMIBREAKUPFragmentPOOLH_
