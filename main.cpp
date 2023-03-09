#include <iostream>
#include <fstream>
#include "MyFermiBreakUp/IntegerPartition.h"
#include "NucleiProperties/NucleiProperties.h"
#include "MyFermiBreakUp/FermiBreakUp.h"
#include "TableValues/NucleiPropertiesTable.h"
#include "TableValues/NucleiPropertiesTableAME12.h"

void DumpTables() {
  std::ofstream th_out("../TheoreticalTable.data");
  std::ofstream pr_out("../PracticalTable.data");
  th_out << NucleiPropertiesTable();
  pr_out << NucleiPropertiesTableAME12();
}

int main() {
  auto vec = LorentzVector(0, 0, 0, NucleiProperties().GetNuclearMass(12_m, 6_c) + 6);
  auto out = FermiBreakUp::BreakItUp(FermiParticle(12_m, 6_c, vec));
  std::cout << out.size();

//  for (auto& partition : IntegerPartition(12, 3, false)) {
//    for (auto el : partition) {
//      std::cout << el << ' ';
//    }
//    std::cout << '\n';
//  }
}
