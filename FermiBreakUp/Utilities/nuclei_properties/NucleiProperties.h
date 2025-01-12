//
// Created by Artem Novikov on 18.02.2023.
//

#ifndef FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H
#define FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H

#include "utilities/DataTypes.h"
#include "utilities/Singleton.h"

#include "VNucleiProperties.h"
#include "impl/FermiNucleiProperties.h"
#include "impl/NativeNucleiProperties.h"
#include "impl/FastNucleiProperties.h"

namespace properties {

    // it is possible to use polymorphism here, but this way no inline table access is possible and it is a bottleneck
    using nuclei_properties = Singleton<FastNucleiProperties>;

    static_assert(std::is_base_of_v<VNucleiProperties, std::remove_reference_t<decltype(nuclei_properties::Instance())>>,
                "Incorrect Nuclei properties class");

} // namespace properties

#endif // FERMIBREAKUP_UTILITIES_NUCLEI_PROPERTIES_NUCLEIPROPERTIES_H
