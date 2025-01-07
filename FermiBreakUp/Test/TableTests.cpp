//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "Utilities/NucleiProperties/NucleiProperties.h"
#include "Utilities/NucleiProperties/DataStorage/CSVNuclearMass.h"

TEST(TableTest, DefaultPropertiesTest) {
  std::ifstream tableData("./smallNucleiData.csv");
  ASSERTTRUE(tableData.is_open());

  std::string headers;
  tableData >> headers;

  int idx;
  properties::NucleiProperties properties;
  while(tableData >> idx) {
    char s;
    MassNumber m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERTTRUE(properties->IsStable(m, c));
    ASSERTEQ(mass, properties->GetNuclearMass(m, c));
  }
}

TEST(TableTest, FilePropertiesTest) {
  std::ifstream tableData("./smallNucleiData.csv");
  ASSERTTRUE(tableData.is_open());

  std::string headers;
  tableData >> headers;

  int idx;
  properties::NucleiProperties properties(properties::CSVNuclearMass("./smallNucleiData.csv"));
  while(tableData >> idx) {
    char s;
    MassNumber m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERTTRUE(properties->IsStable(m, c));
    ASSERTEQ(mass, properties->GetNuclearMass(m, c));
  }
}
