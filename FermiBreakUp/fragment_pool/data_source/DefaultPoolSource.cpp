//
// Created by Artem Novikov on 17.02.2024.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "fragment_pool/fragments/StableFragment.h"
#include "fragment_pool/fragments/B9Fragment.h"
#include "fragment_pool/fragments/Be8Fragment.h"
#include "fragment_pool/fragments/He5Fragment.h"
#include "fragment_pool/fragments/Li5Fragment.h"

#include "DefaultPoolSource.h"

namespace fermi {

using CLHEP::MeV;

DefaultPoolSource::DefaultPoolSource() {
  static const StableFragment Fragment00(  1_m, 0_c,  2,  0.00*MeV ); push_back(&Fragment00);
  static const StableFragment Fragment01(  1_m, 1_c,  2,  0.00*MeV ); push_back(&Fragment01);
  static const StableFragment Fragment02(  2_m, 1_c,  3,  0.00*MeV ); push_back(&Fragment02);
  static const StableFragment Fragment03(  3_m, 1_c,  2,  0.00*MeV ); push_back(&Fragment03);
  static const StableFragment Fragment04(  3_m, 2_c,  2,  0.00*MeV ); push_back(&Fragment04);
  static const StableFragment Fragment05(  4_m, 2_c,  1,  0.00*MeV ); push_back(&Fragment05);
  static const He5Fragment    Fragment06(  5_m, 2_c,  4, 16.76*MeV ); push_back(&Fragment06);  // He5
  static const Li5Fragment    Fragment07(  5_m, 3_c,  4, 16.66*MeV ); push_back(&Fragment07);  // Li5
  static const StableFragment Fragment08(  6_m, 2_c,  1,  0.00*MeV ); push_back(&Fragment08);
  static const StableFragment Fragment09(  6_m, 3_c,  3,  0.00*MeV ); push_back(&Fragment09);

  static const StableFragment Fragment10(  6_m, 3_c,  1,  3.56*MeV ); push_back(&Fragment10);
  static const StableFragment Fragment11(  7_m, 3_c,  4,  0.00*MeV ); push_back(&Fragment11);
  static const StableFragment Fragment12(  7_m, 3_c,  2,  0.48*MeV ); push_back(&Fragment12);
  static const StableFragment Fragment13(  7_m, 4_c,  4,  0.00*MeV ); push_back(&Fragment13);
  static const StableFragment Fragment14(  7_m, 4_c,  2,  0.43*MeV ); push_back(&Fragment14);
  static const StableFragment Fragment15(  8_m, 3_c,  5,  0.00*MeV ); push_back(&Fragment15);
  static const StableFragment Fragment16(  8_m, 3_c,  3,  0.98*MeV ); push_back(&Fragment16);
  static const Be8Fragment    Fragment17(  8_m, 4_c,  1,  0.00*MeV ); push_back(&Fragment17);  // Be8
  static const StableFragment Fragment18(  9_m, 4_c,  4,  0.00*MeV ); push_back(&Fragment18);
  static const B9Fragment     Fragment19(  9_m, 5_c,  4,  0.00*MeV ); push_back(&Fragment19);  // B9

  static const StableFragment Fragment20( 0_m, 4_c,  1,  0.00*MeV ); push_back(&Fragment20);
  static const StableFragment Fragment21( 0_m, 4_c,  5,  3.37*MeV ); push_back(&Fragment21);
  static const StableFragment Fragment22( 0_m, 4_c,  8,  5.96*MeV ); push_back(&Fragment22);
  static const StableFragment Fragment23( 0_m, 4_c,  1,  6.18*MeV ); push_back(&Fragment23);
  static const StableFragment Fragment24( 0_m, 4_c,  5,  6.26*MeV ); push_back(&Fragment24);
  static const StableFragment Fragment25( 0_m, 5_c,  7,  0.00*MeV ); push_back(&Fragment25);
  static const StableFragment Fragment26( 0_m, 5_c,  3,  0.72*MeV ); push_back(&Fragment26);
  static const StableFragment Fragment27( 0_m, 5_c,  1,  1.74*MeV ); push_back(&Fragment27);
  static const StableFragment Fragment28( 0_m, 5_c,  3,  2.15*MeV ); push_back(&Fragment28);
  static const StableFragment Fragment29( 0_m, 5_c,  5,  3.59*MeV ); push_back(&Fragment29);

  static const StableFragment Fragment30( 0_m, 6_c,  3,  0.00*MeV ); push_back(&Fragment30);
  static const StableFragment Fragment31( 0_m, 6_c,  5,  3.35*MeV ); push_back(&Fragment31);
  static const StableFragment Fragment32( 1_m, 5_c,  4,  0.00*MeV ); push_back(&Fragment32);
  static const StableFragment Fragment33( 1_m, 5_c,  2,  2.13*MeV ); push_back(&Fragment33);
  static const StableFragment Fragment34( 1_m, 5_c,  6,  4.44*MeV ); push_back(&Fragment34);
  static const StableFragment Fragment35( 1_m, 5_c,  4,  5.02*MeV ); push_back(&Fragment35);
  static const StableFragment Fragment36( 1_m, 5_c, 10,  6.76*MeV ); push_back(&Fragment36);
  static const StableFragment Fragment37( 1_m, 5_c,  6,  7.29*MeV ); push_back(&Fragment37);
  static const StableFragment Fragment38( 1_m, 5_c,  4,  7.98*MeV ); push_back(&Fragment38);
  static const StableFragment Fragment39( 1_m, 5_c,  6,  8.56*MeV ); push_back(&Fragment39);

  static const StableFragment Fragment40( 1_m, 6_c,  4,  0.00*MeV ); push_back(&Fragment40);
  static const StableFragment Fragment41( 1_m, 6_c,  2,  2.00*MeV ); push_back(&Fragment41);
  static const StableFragment Fragment42( 1_m, 6_c,  6,  4.32*MeV ); push_back(&Fragment42);
  static const StableFragment Fragment43( 1_m, 6_c,  4,  4.80*MeV ); push_back(&Fragment43);
  static const StableFragment Fragment44( 1_m, 6_c,  2,  6.34*MeV ); push_back(&Fragment44);
  static const StableFragment Fragment45( 1_m, 6_c,  8,  6.48*MeV ); push_back(&Fragment45);
  static const StableFragment Fragment46( 1_m, 6_c,  6,  6.90*MeV ); push_back(&Fragment46);
  static const StableFragment Fragment47( 1_m, 6_c,  4,  7.50*MeV ); push_back(&Fragment47);
  static const StableFragment Fragment48( 1_m, 6_c,  4,  8.10*MeV ); push_back(&Fragment48);
  static const StableFragment Fragment49( 1_m, 6_c,  6,  8.42*MeV ); push_back(&Fragment49);

  static const StableFragment Fragment50( 1_m, 6_c,  8,  8.66*MeV ); push_back(&Fragment50);
  static const StableFragment Fragment51( 2_m, 5_c,  3,  0.00*MeV ); push_back(&Fragment51);
  static const StableFragment Fragment52( 2_m, 5_c,  5,  0.95*MeV ); push_back(&Fragment52);
  static const StableFragment Fragment53( 2_m, 5_c,  5,  1.67*MeV ); push_back(&Fragment53);
  static const StableFragment Fragment54( 2_m, 5_c,  4,  2.65*MeV ); push_back(&Fragment54);
  static const StableFragment Fragment55( 2_m, 6_c,  1,  0.00*MeV ); push_back(&Fragment55);
  static const StableFragment Fragment56( 2_m, 6_c,  5,  4.44*MeV ); push_back(&Fragment56);
  static const StableFragment Fragment57( 3_m, 6_c,  2,  0.00*MeV ); push_back(&Fragment57);
  static const StableFragment Fragment58( 3_m, 6_c,  2,  3.09*MeV ); push_back(&Fragment58);
  static const StableFragment Fragment59( 3_m, 6_c,  4,  3.68*MeV ); push_back(&Fragment59);

  static const StableFragment Fragment60( 3_m, 6_c,  6,  3.85*MeV ); push_back(&Fragment60);
  static const StableFragment Fragment61( 3_m, 7_c,  2,  0.00*MeV ); push_back(&Fragment61);
  static const StableFragment Fragment62( 4_m, 6_c,  1,  0.00*MeV ); push_back(&Fragment62);
  static const StableFragment Fragment63( 4_m, 6_c,  3,  6.09*MeV ); push_back(&Fragment63);
  static const StableFragment Fragment64( 4_m, 6_c,  8,  6.69*MeV ); push_back(&Fragment64);
  static const StableFragment Fragment65( 4_m, 6_c,  6,  6.96*MeV ); push_back(&Fragment65);
  static const StableFragment Fragment66( 4_m, 6_c,  5,  7.34*MeV ); push_back(&Fragment66);
  static const StableFragment Fragment67( 4_m, 7_c,  3,  0.00*MeV ); push_back(&Fragment67);
  static const StableFragment Fragment68( 4_m, 7_c,  1,  2.31*MeV ); push_back(&Fragment68);
  static const StableFragment Fragment69( 4_m, 7_c,  3,  3.95*MeV ); push_back(&Fragment69);

  static const StableFragment Fragment70( 4_m, 7_c,  1,  4.92*MeV ); push_back(&Fragment70);
  static const StableFragment Fragment71( 4_m, 7_c,  5,  5.11*MeV ); push_back(&Fragment71);
  static const StableFragment Fragment72( 4_m, 7_c,  3,  5.69*MeV ); push_back(&Fragment72);
  static const StableFragment Fragment73( 4_m, 7_c,  7,  5.83*MeV ); push_back(&Fragment73);
  static const StableFragment Fragment74( 4_m, 7_c,  3,  6.20*MeV ); push_back(&Fragment74);
  static const StableFragment Fragment75( 4_m, 7_c,  7,  6.44*MeV ); push_back(&Fragment75);
  static const StableFragment Fragment76( 4_m, 7_c,  5,  7.03*MeV ); push_back(&Fragment76);
  static const StableFragment Fragment77( 5_m, 7_c,  2,  0.00*MeV ); push_back(&Fragment77);
  static const StableFragment Fragment78( 5_m, 7_c,  8,  5.28*MeV ); push_back(&Fragment78);
  static const StableFragment Fragment79( 5_m, 7_c,  4,  6.32*MeV ); push_back(&Fragment79);

  static const StableFragment Fragment80( 5_m, 7_c, 10,  7.22*MeV ); push_back(&Fragment80);
  static const StableFragment Fragment81( 5_m, 7_c,  8,  7.57*MeV ); push_back(&Fragment81);
  static const StableFragment Fragment82( 5_m, 7_c,  2,  8.31*MeV ); push_back(&Fragment82);
  static const StableFragment Fragment83( 5_m, 7_c,  4,  8.57*MeV ); push_back(&Fragment83);
  static const StableFragment Fragment84( 5_m, 7_c, 14,  9.15*MeV ); push_back(&Fragment84);
  static const StableFragment Fragment85( 5_m, 7_c, 14,  9.79*MeV ); push_back(&Fragment85);
  static const StableFragment Fragment86( 5_m, 7_c,  8, 10.00*MeV ); push_back(&Fragment86);
  static const StableFragment Fragment87( 5_m, 8_c,  2,  0.00*MeV ); push_back(&Fragment87);
  static const StableFragment Fragment88( 5_m, 8_c,  8,  5.22*MeV ); push_back(&Fragment88);
  static const StableFragment Fragment89( 5_m, 8_c,  4,  6.18*MeV ); push_back(&Fragment89);

  static const StableFragment Fragment90( 5_m, 8_c, 10,  6.83*MeV ); push_back(&Fragment90);
  static const StableFragment Fragment91( 5_m, 8_c,  8,  7.28*MeV ); push_back(&Fragment91);
  static const StableFragment Fragment92( 6_m, 7_c,  5,  0.00*MeV ); push_back(&Fragment92);
  static const StableFragment Fragment93( 6_m, 7_c,  1,  0.12*MeV ); push_back(&Fragment93);
  static const StableFragment Fragment94( 6_m, 7_c,  7,  0.30*MeV ); push_back(&Fragment94);
  static const StableFragment Fragment95( 6_m, 7_c,  3,  0.40*MeV ); push_back(&Fragment95);
  static const StableFragment Fragment96( 6_m, 8_c,  1,  0.00*MeV ); push_back(&Fragment96);
  static const StableFragment Fragment97( 6_m, 8_c,  8,  6.10*MeV ); push_back(&Fragment97);
  static const StableFragment Fragment98( 6_m, 8_c,  5,  6.92*MeV ); push_back(&Fragment98);
  static const StableFragment Fragment99( 6_m, 8_c,  3,  7.12*MeV ); push_back(&Fragment99);
}

} // namespace fermi
