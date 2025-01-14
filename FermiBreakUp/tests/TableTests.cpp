//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "util/nuclei_properties/NucleiProperties.h"
#include "util/nuclei_properties/data_storage/CSVNuclearMass.h"

TEST(TableTest, DefaultPropertiesTest) {
  std::ifstream tableData("./smallNucleiData.csv");
  ASSERTTRUE(tableData.is_open());

  std::string headers;
  tableData >> headers;

  int idx;
  fermi::NucleiProperties fermi;
  while(tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERTTRUE(fermi->IsStable(m, c));
    ASSERTEQ(mass, fermi->GetNuclearMass(m, c));
  }
}

TEST(TableTest, FilePropertiesTest) {
  std::ifstream tableData("./smallNucleiData.csv");
  ASSERTTRUE(tableData.is_open());

  std::string headers;
  tableData >> headers;

  int idx;
  fermi::NucleiProperties fermi(fermi::CSVNuclearMass("./smallNucleiData.csv"));
  while(tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERTTRUE(fermi->IsStable(m, c));
    ASSERTEQ(mass, fermi->GetNuclearMass(m, c));
  }
}
