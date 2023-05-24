//
// Created by Artem Novikov on 11.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_VFERMIPROPERTIESBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_VFERMIPROPERTIESBUILDER_H_

#include "../FermiNucleiProperties.h"

class VFermiPropertiesBuilder {
 public:
  virtual void BuildTable(FermiNucleiProperties::MassMap& data) const = 0;

  virtual ~VFermiPropertiesBuilder() = default;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_VFERMIPROPERTIESBUILDER_H_