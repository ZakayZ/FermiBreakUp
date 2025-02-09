//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H

#include "FermiBreakUp/nuclei_properties/impl/FermiNucleiProperties.h"
#include "FermiBreakUp/util/DataTypes.h"
#include "FermiBreakUp/util/Singleton.h"

#include "VNucleiProperties.h"

namespace fbu {
    // it is possible to use polymorphism here
    // but it is a bottleneck and no virtual call is made
    using NucleiProperties = Singleton<FermiNucleiProperties>;

    static_assert(std::is_base_of_v<VNucleiProperties, std::remove_reference_t<decltype(NucleiProperties::Instance())>>,
                "Incorrect Nuclei fbu class");
} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H
