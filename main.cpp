#include <iostream>
#include "MyFermiBreakUp/IntegerPartition.h"

int main() {
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
  return 0;
}
