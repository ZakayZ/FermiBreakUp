//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "utilities/nuclei_properties/NucleiProperties.h"
#include "utilities/nuclei_properties/data_storage/CSVNuclearMass.h"

TEST(TableTest, DefaultPropertiesTest) {
  std::ifstream tableData("./smallNucleiData.csv");
  ASSERTTRUE(tableData.is_open());

  std::string headers;
  tableData >> headers;

  int idx;
  properties::nuclei_properties properties;
  while(tableData >> idx) {
    char s;
    AtomicMass m;
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
  properties::nuclei_properties properties(properties::CSVNuclearMass("./smallNucleiData.csv"));
  while(tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERTTRUE(properties->IsStable(m, c));
    ASSERTEQ(mass, properties->GetNuclearMass(m, c));
  }
}
