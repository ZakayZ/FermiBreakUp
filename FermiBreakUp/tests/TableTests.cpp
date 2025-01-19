//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "util/nuclei_properties/NucleiProperties.h"
#include "util/nuclei_properties/data_storage/CSVNuclearMass.h"

using namespace fermi;

TEST(TableTest, DefaultPropertiesTest) {
  std::ifstream tableData("./small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  FermiStr headers;
  tableData >> headers;

  int idx;
  fermi::NucleiProperties fermi;
  while (tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fermi->IsStable(m, c));
    ASSERT_EQ(mass, fermi->GetNuclearMass(m, c));
  }
}

TEST(TableTest, FilePropertiesTest) {
  std::ifstream tableData("./small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  FermiStr headers;
  tableData >> headers;

  int idx;
  fermi::NucleiProperties fermi(fermi::CSVNuclearMass("./small_nuclei_data.csv"));
  while (tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fermi->IsStable(m, c));
    ASSERT_EQ(mass, fermi->GetNuclearMass(m, c));
  }
}
