//
// Created by Artem Novikov on 08.03.2023.
//

#include <fstream>

#include <gtest/gtest.h>

#include "FermiBreakUp/nuclei_properties/NucleiProperties.h"
#include "FermiBreakUp/nuclei_properties/data_storage/CSVNuclearMass.h"

using namespace fbu;

TEST(TableTest, DefaultProperties) {
  std::ifstream tableData("small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  FermiStr headers;
  tableData >> headers;

  int idx;
  NucleiProperties fbu;
  while (tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fbu->IsStable(m, c));
    ASSERT_EQ(mass, fbu->GetNuclearMass(m, c));
  }
}

TEST(TableTest, FileProperties) {
  std::ifstream tableData("small_nuclei_data.csv");
  ASSERT_TRUE(tableData.is_open());

  FermiStr headers;
  tableData >> headers;

  int idx;
  NucleiProperties fbu(CSVNuclearMass("small_nuclei_data.csv"));
  while (tableData >> idx) {
    char s;
    AtomicMass m;
    ChargeNumber c;
    FermiFloat mass;
    tableData >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(fbu->IsStable(m, c));
    ASSERT_EQ(mass, fbu->GetNuclearMass(m, c));
  }
}
