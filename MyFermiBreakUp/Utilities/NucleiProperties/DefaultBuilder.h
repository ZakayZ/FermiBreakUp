//
// Created by Artem Novikov on 20.05.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_DEFAULTBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_DEFAULTBUILDER_H_

#include "VFermiPropertiesBuilder.h"

class DefaultBuilder : public VFermiPropertiesBuilder {
 public:
  void BuildTable(FermiNucleiProperties::MassMap& data) const override;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_DEFAULTBUILDER_H_
