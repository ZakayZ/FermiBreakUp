//
// Created by Artem Novikov on 17.02.2024.
//

#include <CLHEP/Units/PhysicalConstants.h>

#include "FermiBreakUp/fragment_pool/fragments/StableFragment.h"
#include "FermiBreakUp/fragment_pool/fragments/UnstableFragment.h"

#include "DefaultPoolSource.h"

using CLHEP::MeV;
using namespace fbu;

DefaultPoolSource::DefaultPoolSource() {
  #define INSTANTIATE_MACRO(x, y) __CONCAT(x, y)

  #define ADD_FRAGMENT_IMPL(NAME, VALUE) \
    static const auto NAME = VALUE;      \
    push_back(&NAME);

  // automatic unique names are added
  #define ADD_FRAGMENT(VALUE) ADD_FRAGMENT_IMPL(INSTANTIATE_MACRO(Fragment, __COUNTER__), VALUE)

  ADD_FRAGMENT(StableFragment(  1_m, 0_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  1_m, 1_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  2_m, 1_c,  3,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  3_m, 1_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  3_m, 2_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  4_m, 2_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(He5Fragment(     5_m, 2_c,  4, 16.76*MeV ));
  ADD_FRAGMENT(Li5Fragment(     5_m, 3_c,  4, 16.66*MeV ));
  ADD_FRAGMENT(StableFragment(  6_m, 2_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  6_m, 3_c,  3,  0.00*MeV ));

  ADD_FRAGMENT(StableFragment(  6_m, 3_c,  1,  3.56*MeV ));
  ADD_FRAGMENT(StableFragment(  7_m, 3_c,  4,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  7_m, 3_c,  2,  0.48*MeV ));
  ADD_FRAGMENT(StableFragment(  7_m, 4_c,  4,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  7_m, 4_c,  2,  0.43*MeV ));
  ADD_FRAGMENT(StableFragment(  8_m, 3_c,  5,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  8_m, 3_c,  3,  0.98*MeV ));
  ADD_FRAGMENT(Be8Fragment(     8_m, 4_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment(  9_m, 4_c,  4,  0.00*MeV ));
  ADD_FRAGMENT(B9Fragment(      9_m, 5_c,  4,  0.00*MeV ));

  ADD_FRAGMENT(StableFragment( 10_m, 4_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 4_c,  5,  3.37*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 4_c,  8,  5.96*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 4_c,  1,  6.18*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 4_c,  5,  6.26*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 5_c,  7,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 5_c,  3,  0.72*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 5_c,  1,  1.74*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 5_c,  3,  2.15*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 5_c,  5,  3.59*MeV ));

  ADD_FRAGMENT(StableFragment( 10_m, 6_c,  3,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 10_m, 6_c,  5,  3.35*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  4,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  2,  2.13*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  6,  4.44*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  4,  5.02*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c, 10,  6.76*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  6,  7.29*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  4,  7.98*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 5_c,  6,  8.56*MeV ));

  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  4,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  2,  2.00*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  6,  4.32*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  4,  4.80*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  2,  6.34*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  8,  6.48*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  6,  6.90*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  4,  7.50*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  4,  8.10*MeV ));
  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  6,  8.42*MeV ));

  ADD_FRAGMENT(StableFragment( 11_m, 6_c,  8,  8.66*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 5_c,  3,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 5_c,  5,  0.95*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 5_c,  5,  1.67*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 5_c,  4,  2.65*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 6_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 12_m, 6_c,  5,  4.44*MeV ));
  ADD_FRAGMENT(StableFragment( 13_m, 6_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 13_m, 6_c,  2,  3.09*MeV ));
  ADD_FRAGMENT(StableFragment( 13_m, 6_c,  4,  3.68*MeV ));

  ADD_FRAGMENT(StableFragment( 13_m, 6_c,  6,  3.85*MeV ));
  ADD_FRAGMENT(StableFragment( 13_m, 7_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 6_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 6_c,  3,  6.09*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 6_c,  8,  6.69*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 6_c,  6,  6.96*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 6_c,  5,  7.34*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  3,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  1,  2.31*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  3,  3.95*MeV ));

  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  1,  4.92*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  5,  5.11*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  3,  5.69*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  7,  5.83*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  3,  6.20*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  7,  6.44*MeV ));
  ADD_FRAGMENT(StableFragment( 14_m, 7_c,  5,  7.03*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  8,  5.28*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  4,  6.32*MeV ));

  ADD_FRAGMENT(StableFragment( 15_m, 7_c, 10,  7.22*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  8,  7.57*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  2,  8.31*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  4,  8.57*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c, 14,  9.15*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c, 14,  9.79*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 7_c,  8, 10.00*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 8_c,  2,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 8_c,  8,  5.22*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 8_c,  4,  6.18*MeV ));

  ADD_FRAGMENT(StableFragment( 15_m, 8_c, 10,  6.83*MeV ));
  ADD_FRAGMENT(StableFragment( 15_m, 8_c,  8,  7.28*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 7_c,  5,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 7_c,  1,  0.12*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 7_c,  7,  0.30*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 7_c,  3,  0.40*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 8_c,  1,  0.00*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 8_c,  8,  6.10*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 8_c,  5,  6.92*MeV ));
  ADD_FRAGMENT(StableFragment( 16_m, 8_c,  3,  7.12*MeV ));

  #undef ADD_FRAGMENT
  #undef ADD_FRAGMENT_IMPL
  #undef INSTANTIATE_MACRO
}
