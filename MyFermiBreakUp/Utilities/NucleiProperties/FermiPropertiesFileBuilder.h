//
// Created by Artem Novikov on 11.03.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESFILEBUILDER_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESFILEBUILDER_H_

#include "VFermiPropertiesBuilder.h"

class FermiPropertiesFileBuilder : public VFermiPropertiesBuilder{
 public:
  FermiPropertiesFileBuilder(const std::string& source);

  void BuildTable(FermiNucleiProperties::MassMap& data) const override;
 private:
  std::string source_;
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_UTILITIES_NUCLEIPROPERTIES_FERMIPROPERTIESFILEBUILDER_H_
