//
// Created by Artem Novikov on 08.03.2023.
//

#include <gtest/gtest.h>
#include <fstream>

#include "NucleiProperties/NucleiProperties.h"

TEST(TableTest, PropertiesTest) {
  std::ifstream table_data("../small_nuclei_data.csv");

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