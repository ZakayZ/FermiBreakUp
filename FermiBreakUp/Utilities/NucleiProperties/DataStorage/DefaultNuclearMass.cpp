//
// Created by Artem Novikov on 18.02.2024.
//

#include "DefaultNuclearMass.h"

namespace properties {

DefaultNuclearMass::DefaultNuclearMass() {
  masses_.emplace_back(NucleiData{1_m, 0_c}, 939.565);
  masses_.emplace_back(NucleiData{1_m, 1_c}, 938.272);
  masses_.emplace_back(NucleiData{2_m, 1_c}, 1875.61);
  masses_.emplace_back(NucleiData{3_m, 1_c}, 2808.92);
  masses_.emplace_back(NucleiData{3_m, 2_c}, 2808.39);
  masses_.emplace_back(NucleiData{3_m, 3_c}, 2821.62);
  masses_.emplace_back(NucleiData{4_m, 1_c}, 3750.09);
  masses_.emplace_back(NucleiData{4_m, 2_c}, 3727.38);
  masses_.emplace_back(NucleiData{4_m, 3_c}, 3749.77);
  masses_.emplace_back(NucleiData{5_m, 1_c}, 4689.85);
  masses_.emplace_back(NucleiData{5_m, 2_c}, 4667.68);
  masses_.emplace_back(NucleiData{5_m, 3_c}, 4667.62);
  masses_.emplace_back(NucleiData{5_m, 4_c}, 4692.57);
  masses_.emplace_back(NucleiData{6_m, 1_c}, 5630.33);
  masses_.emplace_back(NucleiData{6_m, 2_c}, 5605.53);
  masses_.emplace_back(NucleiData{6_m, 3_c}, 5601.52);
  masses_.emplace_back(NucleiData{6_m, 4_c}, 5605.3);
  masses_.emplace_back(NucleiData{6_m, 5_c}, 5633.73);
  masses_.emplace_back(NucleiData{7_m, 1_c}, 6569.08);
  masses_.emplace_back(NucleiData{7_m, 2_c}, 6545.51);
  masses_.emplace_back(NucleiData{7_m, 3_c}, 6533.83);
  masses_.emplace_back(NucleiData{7_m, 4_c}, 6534.18);
  masses_.emplace_back(NucleiData{7_m, 5_c}, 6545.58);
  masses_.emplace_back(NucleiData{8_m, 2_c}, 7482.54);
  masses_.emplace_back(NucleiData{8_m, 3_c}, 7471.37);
  masses_.emplace_back(NucleiData{8_m, 4_c}, 7454.85);
  masses_.emplace_back(NucleiData{8_m, 5_c}, 7472.32);
  masses_.emplace_back(NucleiData{8_m, 6_c}, 7483.95);
  masses_.emplace_back(NucleiData{9_m, 2_c}, 8423.36);
  masses_.emplace_back(NucleiData{9_m, 3_c}, 8406.87);
  masses_.emplace_back(NucleiData{9_m, 4_c}, 8392.75);
  masses_.emplace_back(NucleiData{9_m, 5_c}, 8393.31);
  masses_.emplace_back(NucleiData{9_m, 6_c}, 8409.29);
  masses_.emplace_back(NucleiData{0_m, 2_c}, 9363.09);
  masses_.emplace_back(NucleiData{0_m, 3_c}, 9346.46);
  masses_.emplace_back(NucleiData{0_m, 4_c}, 9325.5);
  masses_.emplace_back(NucleiData{0_m, 5_c}, 9324.44);
  masses_.emplace_back(NucleiData{0_m, 6_c}, 9327.57);
  masses_.emplace_back(NucleiData{0_m, 7_c}, 9350.16);
  masses_.emplace_back(NucleiData{1_m, 3_c}, 10285.6);
  masses_.emplace_back(NucleiData{1_m, 4_c}, 10264.6);
  masses_.emplace_back(NucleiData{1_m, 5_c}, 10252.5);
  masses_.emplace_back(NucleiData{1_m, 6_c}, 10254.0);
  masses_.emplace_back(NucleiData{1_m, 7_c}, 10267.2);
  masses_.emplace_back(NucleiData{2_m, 3_c}, 11225.3);
  masses_.emplace_back(NucleiData{2_m, 4_c}, 11201.0);
  masses_.emplace_back(NucleiData{2_m, 5_c}, 11188.7);
  masses_.emplace_back(NucleiData{2_m, 6_c}, 11174.9);
  masses_.emplace_back(NucleiData{2_m, 7_c}, 11191.7);
  masses_.emplace_back(NucleiData{2_m, 8_c}, 11205.8);
  masses_.emplace_back(NucleiData{3_m, 3_c}, 12166.2);
  masses_.emplace_back(NucleiData{3_m, 4_c}, 12141.0);
  masses_.emplace_back(NucleiData{3_m, 5_c}, 12123.4);
  masses_.emplace_back(NucleiData{3_m, 6_c}, 12109.5);
  masses_.emplace_back(NucleiData{3_m, 7_c}, 12111.2);
  masses_.emplace_back(NucleiData{3_m, 8_c}, 12128.5);
  masses_.emplace_back(NucleiData{4_m, 4_c}, 13078.8);
  masses_.emplace_back(NucleiData{4_m, 5_c}, 13062.0);
  masses_.emplace_back(NucleiData{4_m, 6_c}, 13040.9);
  masses_.emplace_back(NucleiData{4_m, 7_c}, 13040.2);
  masses_.emplace_back(NucleiData{4_m, 8_c}, 13044.8);
  masses_.emplace_back(NucleiData{4_m, 9_c}, 13068.3);
  masses_.emplace_back(NucleiData{5_m, 4_c}, 14020.1);
  masses_.emplace_back(NucleiData{5_m, 5_c}, 13998.8);
  masses_.emplace_back(NucleiData{5_m, 6_c}, 13979.2);
  masses_.emplace_back(NucleiData{5_m, 7_c}, 13968.9);
  masses_.emplace_back(NucleiData{5_m, 8_c}, 13971.2);
  masses_.emplace_back(NucleiData{5_m, 9_c}, 13984.6);
  masses_.emplace_back(NucleiData{6_m, 4_c}, 14959.3);
  masses_.emplace_back(NucleiData{6_m, 5_c}, 14938.5);
  masses_.emplace_back(NucleiData{6_m, 6_c}, 14914.5);
  masses_.emplace_back(NucleiData{6_m, 7_c}, 14906.0);
  masses_.emplace_back(NucleiData{6_m, 8_c}, 14895.1);
  masses_.emplace_back(NucleiData{6_m, 9_c}, 14910.0);
  masses_.emplace_back(NucleiData{6_m, 0_c}, 14922.8);
  masses_.emplace_back(NucleiData{7_m, 5_c}, 15876.6);
  masses_.emplace_back(NucleiData{7_m, 6_c}, 15853.4);
  masses_.emplace_back(NucleiData{7_m, 7_c}, 15839.7);
  masses_.emplace_back(NucleiData{7_m, 8_c}, 15830.5);
  masses_.emplace_back(NucleiData{7_m, 9_c}, 15832.8);
  masses_.emplace_back(NucleiData{7_m, 0_c}, 15846.8);
  masses_.emplace_back(NucleiData{8_m, 5_c}, 16816.2);
  masses_.emplace_back(NucleiData{8_m, 6_c}, 16788.7);
  masses_.emplace_back(NucleiData{8_m, 7_c}, 16776.4);
  masses_.emplace_back(NucleiData{8_m, 8_c}, 16762.0);
  masses_.emplace_back(NucleiData{8_m, 9_c}, 16763.2);
  masses_.emplace_back(NucleiData{8_m, 0_c}, 16767.1);
  masses_.emplace_back(NucleiData{8_m, 1_c}, 16786.3);
  masses_.emplace_back(NucleiData{9_m, 5_c}, 17754.6);
  masses_.emplace_back(NucleiData{9_m, 6_c}, 17727.7);
  masses_.emplace_back(NucleiData{9_m, 7_c}, 17710.7);
  masses_.emplace_back(NucleiData{9_m, 8_c}, 17697.6);
  masses_.emplace_back(NucleiData{9_m, 9_c}, 17692.3);
  masses_.emplace_back(NucleiData{9_m, 0_c}, 17695.0);
  masses_.emplace_back(NucleiData{9_m, 1_c}, 17705.7);
  masses_.emplace_back(NucleiData{9_m, 2_c}, 17724.1);
  masses_.emplace_back(NucleiData{0_m, 5_c}, 18694.5);
  masses_.emplace_back(NucleiData{0_m, 6_c}, 18664.4);
  masses_.emplace_back(NucleiData{0_m, 7_c}, 18648.1);
  masses_.emplace_back(NucleiData{0_m, 8_c}, 18629.6);
  masses_.emplace_back(NucleiData{0_m, 9_c}, 18625.3);
  masses_.emplace_back(NucleiData{0_m, 0_c}, 18617.7);
  masses_.emplace_back(NucleiData{0_m, 1_c}, 18631.1);
  masses_.emplace_back(NucleiData{0_m, 2_c}, 18641.3);
}

} // properties
