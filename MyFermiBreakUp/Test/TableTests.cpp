//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "Utilities/NucleiProperties/NucleiProperties.h"
#include "Utilities/NucleiProperties/Builder/CSVBuilder.h"

using namespace properties;

TEST(TableTest, DefaultPropertiesTest) {
  std::ifstream table_data("../Data/small_nuclei_data.csv");
  ASSERT_TRUE(table_data.is_open());

  std::string headers;
  table_data >> headers;

  int idx;
  NucleiProperties properties;
  while(table_data >> idx) {
    char s;
    MassNumber m;
    ChargeNumber c;
    FermiFloat mass;
    table_data >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(properties.IsStable(m, c));
    ASSERT_EQ(mass, properties.GetNuclearMass(m, c));
  }
}

TEST(TableTest, FilePropertiesTest) {
  std::ifstream table_data("../Data/small_nuclei_data.csv");
  ASSERT_TRUE(table_data.is_open());

  std::string headers;
  table_data >> headers;

  int idx;
  NucleiProperties properties(CSVBuilder("../Data/small_nuclei_data.csv"));
  while(table_data >> idx) {
    char s;
    MassNumber m;
    ChargeNumber c;
    FermiFloat mass;
    table_data >> s >> m >> s >> c >> s >> mass;

    ASSERT_TRUE(properties.IsStable(m, c));
    ASSERT_EQ(mass, properties.GetNuclearMass(m, c));
  }
}