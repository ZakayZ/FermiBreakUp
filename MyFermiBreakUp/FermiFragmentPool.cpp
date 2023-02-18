//
// Created by Artem Novikov on 18.02.2023.
//
#include <CLHEP/Units/PhysicalConstants.h>

#include "FermiFragmentPool.h"

#include "StableFermiFragment.h"
#include "UnstableFermiFragment.h"
#include "B9FermiFragment.h"
#include "Be8FermiFragment.h"
#include "He5FermiFragment.h"
#include "Li5FermiFragment.h"

using namespace CLHEP;

std::multimap<NucleiData, const FermiFragment*>* FermiFragmentPool::fragments_pool_ = nullptr;

FermiFragmentPool::FermiFragmentPool() {
  if (fragments_pool_ == nullptr) {
    static const StableFermiFragment Fragment00(  1, 0,  2,  0.00*MeV ); AddFragment(Fragment00);
    static const StableFermiFragment Fragment01(  1, 1,  2,  0.00*MeV ); AddFragment(Fragment01);
    static const StableFermiFragment Fragment02(  2, 1,  3,  0.00*MeV ); AddFragment(Fragment02);
    static const StableFermiFragment Fragment03(  3, 1,  2,  0.00*MeV ); AddFragment(Fragment03);
    static const StableFermiFragment Fragment04(  3, 2,  2,  0.00*MeV ); AddFragment(Fragment04);
    static const StableFermiFragment Fragment05(  4, 2,  1,  0.00*MeV ); AddFragment(Fragment05);
    static const He5FermiFragment    Fragment06(  5, 2,  4, 16.76*MeV ); AddFragment(Fragment06);  /// He5
    static const Li5FermiFragment    Fragment07(  5, 3,  4, 16.66*MeV ); AddFragment(Fragment07);  /// Li5
    static const StableFermiFragment Fragment08(  6, 2,  1,  0.00*MeV ); AddFragment(Fragment08);
    static const StableFermiFragment Fragment09(  6, 3,  3,  0.00*MeV ); AddFragment(Fragment09);

    static const StableFermiFragment Fragment10(  6, 3,  1,  3.56*MeV ); AddFragment(Fragment10);
    static const StableFermiFragment Fragment11(  7, 3,  4,  0.00*MeV ); AddFragment(Fragment11);
    static const StableFermiFragment Fragment12(  7, 3,  2,  0.48*MeV ); AddFragment(Fragment12);
    static const StableFermiFragment Fragment13(  7, 4,  4,  0.00*MeV ); AddFragment(Fragment13);
    static const StableFermiFragment Fragment14(  7, 4,  2,  0.43*MeV ); AddFragment(Fragment14);
    static const StableFermiFragment Fragment15(  8, 3,  5,  0.00*MeV ); AddFragment(Fragment15);
    static const StableFermiFragment Fragment16(  8, 3,  3,  0.98*MeV ); AddFragment(Fragment16);
    static const Be8FermiFragment    Fragment17(  8, 4,  1,  0.00*MeV ); AddFragment(Fragment17);  /// Be8
    static const StableFermiFragment Fragment18(  9, 4,  4,  0.00*MeV ); AddFragment(Fragment18);
    static const B9FermiFragment     Fragment19(  9, 5,  4,  0.00*MeV ); AddFragment(Fragment19);  /// B9

    static const StableFermiFragment Fragment20( 10, 4,  1,  0.00*MeV ); AddFragment(Fragment20);
    static const StableFermiFragment Fragment21( 10, 4,  5,  3.37*MeV ); AddFragment(Fragment21);
    static const StableFermiFragment Fragment22( 10, 4,  8,  5.96*MeV ); AddFragment(Fragment22);
    static const StableFermiFragment Fragment23( 10, 4,  1,  6.18*MeV ); AddFragment(Fragment23);
    static const StableFermiFragment Fragment24( 10, 4,  5,  6.26*MeV ); AddFragment(Fragment24);
    static const StableFermiFragment Fragment25( 10, 5,  7,  0.00*MeV ); AddFragment(Fragment25);
    static const StableFermiFragment Fragment26( 10, 5,  3,  0.72*MeV ); AddFragment(Fragment26);
    static const StableFermiFragment Fragment27( 10, 5,  1,  1.74*MeV ); AddFragment(Fragment27);
    static const StableFermiFragment Fragment28( 10, 5,  3,  2.15*MeV ); AddFragment(Fragment28);
    static const StableFermiFragment Fragment29( 10, 5,  5,  3.59*MeV ); AddFragment(Fragment29);

    static const StableFermiFragment Fragment30( 10, 6,  3,  0.00*MeV ); AddFragment(Fragment30);
    static const StableFermiFragment Fragment31( 10, 6,  5,  3.35*MeV ); AddFragment(Fragment31);
    static const StableFermiFragment Fragment32( 11, 5,  4,  0.00*MeV ); AddFragment(Fragment32);
    static const StableFermiFragment Fragment33( 11, 5,  2,  2.13*MeV ); AddFragment(Fragment33);
    static const StableFermiFragment Fragment34( 11, 5,  6,  4.44*MeV ); AddFragment(Fragment34);
    static const StableFermiFragment Fragment35( 11, 5,  4,  5.02*MeV ); AddFragment(Fragment35);
    static const StableFermiFragment Fragment36( 11, 5, 10,  6.76*MeV ); AddFragment(Fragment36);
    static const StableFermiFragment Fragment37( 11, 5,  6,  7.29*MeV ); AddFragment(Fragment37);
    static const StableFermiFragment Fragment38( 11, 5,  4,  7.98*MeV ); AddFragment(Fragment38);
    static const StableFermiFragment Fragment39( 11, 5,  6,  8.56*MeV ); AddFragment(Fragment39);

    static const StableFermiFragment Fragment40( 11, 6,  4,  0.00*MeV ); AddFragment(Fragment40);
    static const StableFermiFragment Fragment41( 11, 6,  2,  2.00*MeV ); AddFragment(Fragment41);
    static const StableFermiFragment Fragment42( 11, 6,  6,  4.32*MeV ); AddFragment(Fragment42);
    static const StableFermiFragment Fragment43( 11, 6,  4,  4.80*MeV ); AddFragment(Fragment43);
    static const StableFermiFragment Fragment44( 11, 6,  2,  6.34*MeV ); AddFragment(Fragment44);
    static const StableFermiFragment Fragment45( 11, 6,  8,  6.48*MeV ); AddFragment(Fragment45);
    static const StableFermiFragment Fragment46( 11, 6,  6,  6.90*MeV ); AddFragment(Fragment46);
    static const StableFermiFragment Fragment47( 11, 6,  4,  7.50*MeV ); AddFragment(Fragment47);
    static const StableFermiFragment Fragment48( 11, 6,  4,  8.10*MeV ); AddFragment(Fragment48);
    static const StableFermiFragment Fragment49( 11, 6,  6,  8.42*MeV ); AddFragment(Fragment49);

    static const StableFermiFragment Fragment50( 11, 6,  8,  8.66*MeV ); AddFragment(Fragment50);
    static const StableFermiFragment Fragment51( 12, 5,  3,  0.00*MeV ); AddFragment(Fragment51);
    static const StableFermiFragment Fragment52( 12, 5,  5,  0.95*MeV ); AddFragment(Fragment52);
    static const StableFermiFragment Fragment53( 12, 5,  5,  1.67*MeV ); AddFragment(Fragment53);
    static const StableFermiFragment Fragment54( 12, 5,  4,  2.65*MeV ); AddFragment(Fragment54);
    static const StableFermiFragment Fragment55( 12, 6,  1,  0.00*MeV ); AddFragment(Fragment55);
    static const StableFermiFragment Fragment56( 12, 6,  5,  4.44*MeV ); AddFragment(Fragment56);
    static const StableFermiFragment Fragment57( 13, 6,  2,  0.00*MeV ); AddFragment(Fragment57);
    static const StableFermiFragment Fragment58( 13, 6,  2,  3.09*MeV ); AddFragment(Fragment58);
    static const StableFermiFragment Fragment59( 13, 6,  4,  3.68*MeV ); AddFragment(Fragment59);

    static const StableFermiFragment Fragment60( 13, 6,  6,  3.85*MeV ); AddFragment(Fragment60);
    static const StableFermiFragment Fragment61( 13, 7,  2,  0.00*MeV ); AddFragment(Fragment61);
    static const StableFermiFragment Fragment62( 14, 6,  1,  0.00*MeV ); AddFragment(Fragment62);
    static const StableFermiFragment Fragment63( 14, 6,  3,  6.09*MeV ); AddFragment(Fragment63);
    static const StableFermiFragment Fragment64( 14, 6,  8,  6.69*MeV ); AddFragment(Fragment64);
    static const StableFermiFragment Fragment65( 14, 6,  6,  6.96*MeV ); AddFragment(Fragment65);
    static const StableFermiFragment Fragment66( 14, 6,  5,  7.34*MeV ); AddFragment(Fragment66);
    static const StableFermiFragment Fragment67( 14, 7,  3,  0.00*MeV ); AddFragment(Fragment67);
    static const StableFermiFragment Fragment68( 14, 7,  1,  2.31*MeV ); AddFragment(Fragment68);
    static const StableFermiFragment Fragment69( 14, 7,  3,  3.95*MeV ); AddFragment(Fragment69);

    static const StableFermiFragment Fragment70( 14, 7,  1,  4.92*MeV ); AddFragment(Fragment70);
    static const StableFermiFragment Fragment71( 14, 7,  5,  5.11*MeV ); AddFragment(Fragment71);
    static const StableFermiFragment Fragment72( 14, 7,  3,  5.69*MeV ); AddFragment(Fragment72);
    static const StableFermiFragment Fragment73( 14, 7,  7,  5.83*MeV ); AddFragment(Fragment73);
    static const StableFermiFragment Fragment74( 14, 7,  3,  6.20*MeV ); AddFragment(Fragment74);
    static const StableFermiFragment Fragment75( 14, 7,  7,  6.44*MeV ); AddFragment(Fragment75);
    static const StableFermiFragment Fragment76( 14, 7,  5,  7.03*MeV ); AddFragment(Fragment76);
    static const StableFermiFragment Fragment77( 15, 7,  2,  0.00*MeV ); AddFragment(Fragment77);
    static const StableFermiFragment Fragment78( 15, 7,  8,  5.28*MeV ); AddFragment(Fragment78);
    static const StableFermiFragment Fragment79( 15, 7,  4,  6.32*MeV ); AddFragment(Fragment79);

    static const StableFermiFragment Fragment80( 15, 7, 10,  7.22*MeV ); AddFragment(Fragment80);
    static const StableFermiFragment Fragment81( 15, 7,  8,  7.57*MeV ); AddFragment(Fragment81);
    static const StableFermiFragment Fragment82( 15, 7,  2,  8.31*MeV ); AddFragment(Fragment82);
    static const StableFermiFragment Fragment83( 15, 7,  4,  8.57*MeV ); AddFragment(Fragment83);
    static const StableFermiFragment Fragment84( 15, 7, 14,  9.15*MeV ); AddFragment(Fragment84);
    static const StableFermiFragment Fragment85( 15, 7, 14,  9.79*MeV ); AddFragment(Fragment85);
    static const StableFermiFragment Fragment86( 15, 7,  8, 10.00*MeV ); AddFragment(Fragment86);
    static const StableFermiFragment Fragment87( 15, 8,  2,  0.00*MeV ); AddFragment(Fragment87);
    static const StableFermiFragment Fragment88( 15, 8,  8,  5.22*MeV ); AddFragment(Fragment88);
    static const StableFermiFragment Fragment89( 15, 8,  4,  6.18*MeV ); AddFragment(Fragment89);

    static const StableFermiFragment Fragment90( 15, 8, 10,  6.83*MeV ); AddFragment(Fragment90);
    static const StableFermiFragment Fragment91( 15, 8,  8,  7.28*MeV ); AddFragment(Fragment91);
    static const StableFermiFragment Fragment92( 16, 7,  5,  0.00*MeV ); AddFragment(Fragment92);
    static const StableFermiFragment Fragment93( 16, 7,  1,  0.12*MeV ); AddFragment(Fragment93);
    static const StableFermiFragment Fragment94( 16, 7,  7,  0.30*MeV ); AddFragment(Fragment94);
    static const StableFermiFragment Fragment95( 16, 7,  3,  0.40*MeV ); AddFragment(Fragment95);
    static const StableFermiFragment Fragment96( 16, 8,  1,  0.00*MeV ); AddFragment(Fragment96);
    static const StableFermiFragment Fragment97( 16, 8,  8,  6.10*MeV ); AddFragment(Fragment97);
    static const StableFermiFragment Fragment98( 16, 8,  5,  6.92*MeV ); AddFragment(Fragment98);
    static const StableFermiFragment Fragment99( 16, 8,  3,  7.12*MeV ); AddFragment(Fragment99);
  }
}

size_t FermiFragmentPool::Count(uint32_t mass_number, uint32_t charge_number) const {
  return Count({mass_number, charge_number});
}

size_t FermiFragmentPool::Count(const NucleiData& nuclei) const {
  return fragments_pool_->count(nuclei);
}

void FermiFragmentPool::AddFragment(const FermiFragment& fragment) const {
  fragments_pool_->emplace(
    NucleiData{.mass_number = fragment.GetMassNumber(), .charge_number = fragment.GetChargeNumber()}, &fragment);
}

FermiFragmentPool::RangeIterators FermiFragmentPool::GetFragments(uint32_t mass_number, uint32_t charge_number) const {
  return GetFragments({mass_number, charge_number});
}

FermiFragmentPool::RangeIterators FermiFragmentPool::GetFragments(const NucleiData& nuclei) const {
  return fragments_pool_->equal_range(nuclei);
}
