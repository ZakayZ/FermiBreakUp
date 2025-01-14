//
// Created by Artem Novikov on 17.02.2024.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "fragment_pool/fragments/StableFragment.h"
#include "fragment_pool/fragments/UnstableFragment.h"

#include "DefaultPoolSource.h"

using CLHEP::MeV;

using namespace fermi;

DefaultPoolSource::DefaultPoolSource() {
  #define ADD_FRAGMENT(NAME, VALUE) \
    static const auto NAME = VALUE; \
    push_back(&NAME);

  ADD_FRAGMENT(Fragment00, StableFragment( 1_m, 0_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment01, StableFragment( 1_m, 1_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment02, StableFragment( 2_m, 1_c,  3,  0.00*MeV));
  ADD_FRAGMENT(Fragment03, StableFragment( 3_m, 1_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment04, StableFragment( 3_m, 2_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment05, StableFragment( 4_m, 2_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment06, He5Fragment(    5_m, 2_c,  4, 16.76*MeV));
  ADD_FRAGMENT(Fragment07, Li5Fragment(    5_m, 3_c,  4, 16.66*MeV));
  ADD_FRAGMENT(Fragment08, StableFragment( 6_m, 2_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment09, StableFragment( 6_m, 3_c,  3,  0.00*MeV));

  ADD_FRAGMENT(Fragment10, StableFragment( 6_m, 3_c,  1,  3.56*MeV));
  ADD_FRAGMENT(Fragment11, StableFragment( 7_m, 3_c,  4,  0.00*MeV));
  ADD_FRAGMENT(Fragment12, StableFragment( 7_m, 3_c,  2,  0.48*MeV));
  ADD_FRAGMENT(Fragment13, StableFragment( 7_m, 4_c,  4,  0.00*MeV));
  ADD_FRAGMENT(Fragment14, StableFragment( 7_m, 4_c,  2,  0.43*MeV));
  ADD_FRAGMENT(Fragment15, StableFragment( 8_m, 3_c,  5,  0.00*MeV));
  ADD_FRAGMENT(Fragment16, StableFragment( 8_m, 3_c,  3,  0.98*MeV));
  ADD_FRAGMENT(Fragment17, Be8Fragment(    8_m, 4_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment18, StableFragment( 9_m, 4_c,  4,  0.00*MeV));
  ADD_FRAGMENT(Fragment19, B9Fragment(     9_m, 5_c,  4,  0.00*MeV));

  ADD_FRAGMENT(Fragment20, StableFragment( 0_m, 4_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment21, StableFragment( 0_m, 4_c,  5,  3.37*MeV));
  ADD_FRAGMENT(Fragment22, StableFragment( 0_m, 4_c,  8,  5.96*MeV));
  ADD_FRAGMENT(Fragment23, StableFragment( 0_m, 4_c,  1,  6.18*MeV));
  ADD_FRAGMENT(Fragment24, StableFragment( 0_m, 4_c,  5,  6.26*MeV));
  ADD_FRAGMENT(Fragment25, StableFragment( 0_m, 5_c,  7,  0.00*MeV));
  ADD_FRAGMENT(Fragment26, StableFragment( 0_m, 5_c,  3,  0.72*MeV));
  ADD_FRAGMENT(Fragment27, StableFragment( 0_m, 5_c,  1,  1.74*MeV));
  ADD_FRAGMENT(Fragment28, StableFragment( 0_m, 5_c,  3,  2.15*MeV));
  ADD_FRAGMENT(Fragment29, StableFragment( 0_m, 5_c,  5,  3.59*MeV));

  ADD_FRAGMENT(Fragment30, StableFragment( 0_m, 6_c,  3,  0.00*MeV));
  ADD_FRAGMENT(Fragment31, StableFragment( 0_m, 6_c,  5,  3.35*MeV));
  ADD_FRAGMENT(Fragment32, StableFragment( 1_m, 5_c,  4,  0.00*MeV));
  ADD_FRAGMENT(Fragment33, StableFragment( 1_m, 5_c,  2,  2.13*MeV));
  ADD_FRAGMENT(Fragment34, StableFragment( 1_m, 5_c,  6,  4.44*MeV));
  ADD_FRAGMENT(Fragment35, StableFragment( 1_m, 5_c,  4,  5.02*MeV));
  ADD_FRAGMENT(Fragment36, StableFragment( 1_m, 5_c, 10,  6.76*MeV));
  ADD_FRAGMENT(Fragment37, StableFragment( 1_m, 5_c,  6,  7.29*MeV));
  ADD_FRAGMENT(Fragment38, StableFragment( 1_m, 5_c,  4,  7.98*MeV));
  ADD_FRAGMENT(Fragment39, StableFragment( 1_m, 5_c,  6,  8.56*MeV));

  ADD_FRAGMENT(Fragment40, StableFragment( 1_m, 6_c,  4,  0.00*MeV));
  ADD_FRAGMENT(Fragment41, StableFragment( 1_m, 6_c,  2,  2.00*MeV));
  ADD_FRAGMENT(Fragment42, StableFragment( 1_m, 6_c,  6,  4.32*MeV));
  ADD_FRAGMENT(Fragment43, StableFragment( 1_m, 6_c,  4,  4.80*MeV));
  ADD_FRAGMENT(Fragment44, StableFragment( 1_m, 6_c,  2,  6.34*MeV));
  ADD_FRAGMENT(Fragment45, StableFragment( 1_m, 6_c,  8,  6.48*MeV));
  ADD_FRAGMENT(Fragment46, StableFragment( 1_m, 6_c,  6,  6.90*MeV));
  ADD_FRAGMENT(Fragment47, StableFragment( 1_m, 6_c,  4,  7.50*MeV));
  ADD_FRAGMENT(Fragment48, StableFragment( 1_m, 6_c,  4,  8.10*MeV));
  ADD_FRAGMENT(Fragment49, StableFragment( 1_m, 6_c,  6,  8.42*MeV));

  ADD_FRAGMENT(Fragment50, StableFragment( 1_m, 6_c,  8,  8.66*MeV));
  ADD_FRAGMENT(Fragment51, StableFragment( 2_m, 5_c,  3,  0.00*MeV));
  ADD_FRAGMENT(Fragment52, StableFragment( 2_m, 5_c,  5,  0.95*MeV));
  ADD_FRAGMENT(Fragment53, StableFragment( 2_m, 5_c,  5,  1.67*MeV));
  ADD_FRAGMENT(Fragment54, StableFragment( 2_m, 5_c,  4,  2.65*MeV));
  ADD_FRAGMENT(Fragment55, StableFragment( 2_m, 6_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment56, StableFragment( 2_m, 6_c,  5,  4.44*MeV));
  ADD_FRAGMENT(Fragment57, StableFragment( 3_m, 6_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment58, StableFragment( 3_m, 6_c,  2,  3.09*MeV));
  ADD_FRAGMENT(Fragment59, StableFragment( 3_m, 6_c,  4,  3.68*MeV));

  ADD_FRAGMENT(Fragment60, StableFragment( 3_m, 6_c,  6,  3.85*MeV));
  ADD_FRAGMENT(Fragment61, StableFragment( 3_m, 7_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment62, StableFragment( 4_m, 6_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment63, StableFragment( 4_m, 6_c,  3,  6.09*MeV));
  ADD_FRAGMENT(Fragment64, StableFragment( 4_m, 6_c,  8,  6.69*MeV));
  ADD_FRAGMENT(Fragment65, StableFragment( 4_m, 6_c,  6,  6.96*MeV));
  ADD_FRAGMENT(Fragment66, StableFragment( 4_m, 6_c,  5,  7.34*MeV));
  ADD_FRAGMENT(Fragment67, StableFragment( 4_m, 7_c,  3,  0.00*MeV));
  ADD_FRAGMENT(Fragment68, StableFragment( 4_m, 7_c,  1,  2.31*MeV));
  ADD_FRAGMENT(Fragment69, StableFragment( 4_m, 7_c,  3,  3.95*MeV));

  ADD_FRAGMENT(Fragment70, StableFragment( 4_m, 7_c,  1,  4.92*MeV));
  ADD_FRAGMENT(Fragment71, StableFragment( 4_m, 7_c,  5,  5.11*MeV));
  ADD_FRAGMENT(Fragment72, StableFragment( 4_m, 7_c,  3,  5.69*MeV));
  ADD_FRAGMENT(Fragment73, StableFragment( 4_m, 7_c,  7,  5.83*MeV));
  ADD_FRAGMENT(Fragment74, StableFragment( 4_m, 7_c,  3,  6.20*MeV));
  ADD_FRAGMENT(Fragment75, StableFragment( 4_m, 7_c,  7,  6.44*MeV));
  ADD_FRAGMENT(Fragment76, StableFragment( 4_m, 7_c,  5,  7.03*MeV));
  ADD_FRAGMENT(Fragment77, StableFragment( 5_m, 7_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment78, StableFragment( 5_m, 7_c,  8,  5.28*MeV));
  ADD_FRAGMENT(Fragment79, StableFragment( 5_m, 7_c,  4,  6.32*MeV));

  ADD_FRAGMENT(Fragment80, StableFragment( 5_m, 7_c, 10,  7.22*MeV));
  ADD_FRAGMENT(Fragment81, StableFragment( 5_m, 7_c,  8,  7.57*MeV));
  ADD_FRAGMENT(Fragment82, StableFragment( 5_m, 7_c,  2,  8.31*MeV));
  ADD_FRAGMENT(Fragment83, StableFragment( 5_m, 7_c,  4,  8.57*MeV));
  ADD_FRAGMENT(Fragment84, StableFragment( 5_m, 7_c, 14,  9.15*MeV));
  ADD_FRAGMENT(Fragment85, StableFragment( 5_m, 7_c, 14,  9.79*MeV));
  ADD_FRAGMENT(Fragment86, StableFragment( 5_m, 7_c,  8, 10.00*MeV));
  ADD_FRAGMENT(Fragment87, StableFragment( 5_m, 8_c,  2,  0.00*MeV));
  ADD_FRAGMENT(Fragment88, StableFragment( 5_m, 8_c,  8,  5.22*MeV));
  ADD_FRAGMENT(Fragment89, StableFragment( 5_m, 8_c,  4,  6.18*MeV));

  ADD_FRAGMENT(Fragment90, StableFragment( 5_m, 8_c, 10,  6.83*MeV));
  ADD_FRAGMENT(Fragment91, StableFragment( 5_m, 8_c,  8,  7.28*MeV));
  ADD_FRAGMENT(Fragment92, StableFragment( 6_m, 7_c,  5,  0.00*MeV));
  ADD_FRAGMENT(Fragment93, StableFragment( 6_m, 7_c,  1,  0.12*MeV));
  ADD_FRAGMENT(Fragment94, StableFragment( 6_m, 7_c,  7,  0.30*MeV));
  ADD_FRAGMENT(Fragment95, StableFragment( 6_m, 7_c,  3,  0.40*MeV));
  ADD_FRAGMENT(Fragment96, StableFragment( 6_m, 8_c,  1,  0.00*MeV));
  ADD_FRAGMENT(Fragment97, StableFragment( 6_m, 8_c,  8,  6.10*MeV));
  ADD_FRAGMENT(Fragment98, StableFragment( 6_m, 8_c,  5,  6.92*MeV));
  ADD_FRAGMENT(Fragment99, StableFragment( 6_m, 8_c,  3,  7.12*MeV));

  #undef ADD_FRAGMENT
}
