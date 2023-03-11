//
// Created by Artem Novikov on 11.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESBUILDER_H_

#include "VFermiPropertiesBuilder.h"
#include "FermiPropertiesFileBuilder.h"

using PropertiesBuilder = FermiPropertiesFileBuilder;

static_assert(std::is_base_of<VFermiPropertiesBuilder, PropertiesBuilder>::value,
              "PropertiesBuilder must be inherited from VFermiPropertiesBuilder");

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESBUILDER_H_
