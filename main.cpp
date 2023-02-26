#include <iostream>
#include "MyFermiBreakUp/IntegerPartition.h"
#include "MyFermiBreakUp/FermiBreakUp.h"

void PartitionTest() {
  std::cout << "with zero:\n";
  for(auto& partition: IntegerPartition(20, 6, true)) {
    for(auto el: partition) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }

  std::cout << "\nwithout zero:\n";
  for(auto& partition: IntegerPartition(20, 6, false)) {
    for(auto el: partition) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }
}


int main() {
  FermiBreakUp::BreakItUp(FermiParticle(3, 2, LorentzVector(1, 2, 3, 4)));
}
