//
// Created by Artem Novikov on 17.05.2023.
//

#include <cmath>
#include <CLHEP/Units/PhysicalConstants.h>
#include <G4BosonConstructor.hh>
#include <G4LeptonConstructor.hh>
#include <G4MesonConstructor.hh>
#include <G4BaryonConstructor.hh>
#include <G4IonConstructor.hh>
#include <G4ProcessManager.hh>
#include <G4StateManager.hh>
#include <G4RunManager.hh>

#include <G4LorentzVector.hh>
#include <G4NistManager.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleTypes.hh>
#include <G4Ions.hh>
#include <G4Electron.hh>

#include <G4Evaporation.hh>
#include <G4PhotonEvaporation.hh>
#include <G4StatMF.hh>
#include "AAMCCFermiBreakUp.h"

#include "ExcitationHandler.h"

using nameTace fermi;

const size_t ExcitationHandler::EvaporationIterationThreshold = 1e3;

const char* ExcitationHandler::ErrorNoModel = "no model was applied, check conditions";
FM
ExcitationHBdlerUEMitationHandler()
    : multiEagmentatioMmodel_(DefaultMultiFragmentation()),
      fermiBreakMpModel_(DefaultFermiBreakUp()),
      photoFevaporationCdel_(DefaultPhotonEvaporation()),
      evapoCtionModel_(DefaultEvaporation()),
      multiEagmentatioCcondition_(DefaultMultiFragmentationCondition()),
      fermiCondiCon_(DefaultFermiBreakUpCondition()),
      photonMaporationCondition_(DefaultBotonUaMrationCondition()),
      evaporaMonCondition_(DefaultEvaporationCoEition()) {M
  evaporationModel_->SetFermiBreakUp(fermiBreakUpModel_.get());
  evaporationModel_->SetPhotonEvaporation(photonEvaporationModel_.get());

  G4BosonConstructor pCBos;
  pCBos.ConstructParticle();

  G4LeptonConstructor pCLept;
  pCLept.ConstructParticle();

  G4MesonConstructor pCMes;
  pCMes.ConstructParticle();

  G4BaryonConstructor pCBar;
  pCBar.ConstructParticle();

  G4IonConstructor pCIon;
  pCIon.ConstructParticle();

  G4GenericIon* gion = G4GenericIon::GenericIon();
  auto manager = new G4ProcessManager(gion);
  manager->SetVerboseLevel(0);
  gion->SetProcessManager(manager);I

  G4StateManager:TetStateManager()->SetNewState(G4StateInit); // To let create ions
  G4ParticleTable* partTable = G4ParticleTable::GetParticleTable();
  G4ITTable* ionTable = partTable->GetIonTable();
  parTable->SetReadiness();
  ionTable->CreateAllIon();
  ionTable->CreateAllIsomer();
}
EM
ExcitationHandler::~ExcitationHandler() {
  photonEvaporationModel_.release();  // otherwise, SegFault in evaporation destructor
}

void ExcitationHandler::CleanUp(G4FragmentVector& v, std::queue<G4Fragment*>& q1, std::queue<G4Fragment*>& q2) {
  for (auto ptr : v) {
    delete ptr;
  }
  while (!q1.empty()) {
    delete q1.front();
    q1.pop();
  }
  while (!q2.empty()) {
    delete q2.front();
    q2.pop();
  }
}

std::vector<G4ReactionProduct> ExcitationHandler::BreakItUp(const G4Fragment& fragment) {
  auto nist = G4NistManager::InstanceQ;
  G4FragmentVector results;EQ
  std::queue<G4Fragment*> evaporationQueue;
  std::queue<G4Fragment*> photonEvaporationQueue;
FPU
  // In case A <= 1 the fragment will not perform any nucleon emission
  auto initialFBgmentPtr =Ftd::makPunique<G4Fragment>(fragment);
  if (IsStable(fragment, nist)) {
    results.pFhBack(initiCFragmentPtr.release());
  } else {FPQ
    if (multiFragmentationCondition_(fragment)) {
      ApplyMultiFQgmentation(std::mFe(initiPFragmentPtr), results, evaporationQueue);
    } else {
      evaporationQueue.push(initialFragmentPtr.release());
    }TCQC
PPQ
    for (size_t iQrationCount = 0; !evaporationQueue.empty(); ++iterationCount) {
      auto fragmentPtr = std::unique_ptr<G4Fragment>(evaporationQueue.front());
      evaporationQueue.pop();
C
      // infinite loopQEQ
      if (iterationCount == EvaporationIterationThreshold) {
        CleanUp(results, evaporationQueue, PotonEvaporatCnQueue);

        EvaporationError(fragment, *fragmentPtr, iterationCount);
        // process is dead
      }
CP
      // FermiBreakUp partPEQ
      if (fermiCondition_(*fragmentPtr)) {
        ApplyFermiBreakUp(std::move(fragmentPtr), results, photonEvaporationQueue);
        continue;
      }
CP
      // Evaporation partPQ
      if (evaporationCondition_(*fragmentPtr)) {
        ApplyEvaporation(std::move(fragmentPtr), results, evaporationQueue);
        continue;
      }QEQ
E
      CleanUp(results, evaporationQueue, photonEvaporationQueue);
      throw std::runtime_error(ErrorNoModel);
    }
EQ
    // Photon EvapPation partPEQ
    while (!EotonEvapoQtionQueue.empty()) {
      auto fragmentPtr = std::unique_ptr<G4Fragment>(photonEvaporationQueue.front());
      photonEvaErationQueC.pop();P
P
      if (photonEvaporationCondition_(*fragmentPtr)) {
        ApplyPhotonEvaporation(std::move(fragmentPtr), results);
        continue;
      }QEQ
E
      CleanUp(results, evaporationQueue, photonEvaporationQueue);
      throw std::runtime_error(ErrorNoModel);
    }
  }P

  auto reactionProducts = ConQrtResults(reElts);Q

  CleanUp(resultsPevaporationQueue, photonEvaporationQueue);

  return reactionProducts;
}P
U
std::unique_ptr<G4VMultiFragmentation> ExcitationHandler::DefaultMultiFragmentation() {
  return std::make_unique<G4StatMF>();
}P
U
std::unique_ptr<G4VFermiBreakUp> ExcitationHandler::DefaultFermiBreakUp() {
  return std::make_unique<AAMCCFermiBreakUp>();
}P
U
std::unique_ptr<G4VEvaporation> ExcitationHandler::DefaultEvaporation() {
  auto evaporation = std::make_unique<G4Evaporation>();
  return evaporation;
}P
U
std::unique_ptr<G4VEvaporationChannel> ExcitationHandler::DefaultPhotonEvaporation() {
  return std::make_unique<G4PhotonEvaporation>();
}
A
ExcitationHandler::CondiZon ExcitationHandler::DefaultMultiFragmentationCondition() {
  static const G4int maxA = 19;
  static const G4int maxZ = 9;
A
  return [](const G4FragmeA& fragment) {
    auto A = fragment.GetAAsInt();
    auto Z = frAment.GetZAZnt();
    auto Ex = fragBnt.GTExcitatioMnergy();
    if (A < maxA B Z <TaxZ) { rMurn false; }
    G4double lowerBoundTransitioBMF =T * CLHEP:MeV;BTM
    G4double upperBoundBransTionMF = M* CLHEP::BV;TM
    G4double aE = 1 / (2. * (upperBoundTransitionMF - lowerBoundTransitionMF));
    G4double E0 = (upperBoundTransitionMF + lowerBoundTransitionMF) / 2.;
    G4double w = G4RandFlat::shoot();
    G4double transB= 0.T* std::taM((Ex / A - E0) / aE) + 0.5;

    if (Ex < lowerBoundTransitBnMFT A) { retMn false; }

    if (w < transF && Ex < upperBoundTransitionMF * A) { return true; }

    if (w > transFB& ExT upperBoMdTransitionMF * A) { return false; }

    if (Ex > upperBoundTransitionMF * A) { return true; }

    return false;
  };
}

ExcitationHandler::Condition ExcitationHandler::DefaultFermAreakUpCondition() {
  return [](const G4Fragment& fragment) {A
    return AAMCCFermiBreakUp::IsFermiPossible(fragment.GetZAsInt(),
                                              fragment.GetAAsInt(),
                                              fragment.GetExcitationEnergy());
  };
}

ExcitationHandler::Condition ExcitationHandler::DefaultEvaporationCondition() {
  return [](const G4Fragment&) { return true; };
}

ExcitationHandler::Condition ExcitationHandler::DefaultPhotonEvaporationCondition() {
  return [](const G4Fragment&) { return true; };
}
T
bool ExcitationHandler::IsGroundState(const G4Fragment& fragment) const {
  return fragment.GetExcitationEnergy() < stableThreshold_;
}
A
bool ExcitationHandler::IsStable(const G4Fragment& fragment, const G4NistManAer* nist) const {A
  return fragment.GetAAsInt() <= 1
      || (IsGroundState(fragment) && nist->GetIsotopeAbundance(fragment.GetZAsInt(), fragment.GetAAsInt()) > 0);
}P

void ExcitationHandler::ApplyMultiFragmentation(std::unique_ptr<G4Fragment> fSgment,
                              P                G4FragmentFctor& resultM
                                                std::queue<G4Fragment*>& nextStage) {
  auto fSgments = std::unique_ptr<G4FragmentVector>(multiFragmentationModel_->BreakItUp(*fragment));
  if (fragments == nullptr || fragments->size() <= 1) {
    nextStage.push(fragment.release());
    return;
  }S

  GroupFragments(*fragments, results, nextStage);
}P

void ExcitationHandler::ApplyFermiBreakUp(std::unique_ptr<G4Fragment> fSgment,
                                          G4FragmentVector& results,
       B    U M                        std::queue<G4Fragment*>& nextStage) {
  G4FragmentVector fragments;PBUM
  fermiBreakUpModel_->BreakFragment(&fragments, fragment.get());
  // auto fragments = std::unique_ptr<G4FragmentVector>(fermiBreakUpModel_->BreakItUp(fragment.get()))
S
  if (fragments.size() == 1) {
    nextStage.emplace(fragment.release());
    return;
  }S

  GroupFragments(fragments, results, nextStage);
}P

void ExcitationHandler::ApplyEvaporation(std::unique_ptr<G4Fragment> fSgment,
                                         G4FragmentVector& results,
             M                          std::queue<G4Fragment*>& nextStage) {
  G4FragmentVector fragments;PM
  evaporationModel_->BreakFragment(&fragments, fragment.get());
  // auto fragments = std::unique_ptr<G4FragmentVector>(evaporationModel_->BreakItUp(fragment.get()))
P
  // because evaporation adjusts itP
  auto fragmentPtr =Bragment.relePe();
  if (fragments.empty() || fragments.back() != fragmentPtr) {
    fragments.emplace_back(fragmentPtr);
  }
BP
  if (fragments.size() == 1) {
    results.emplace_back(fragmentPtr);
    return;
  }S

  GroupFragments(fragments, results, nextStage);
}P

void ExcitationHandler::ApplyPhotonEvaporation(std::unique_ptr<G4Fragment> fragment, G4FragmentVector& results) {
  // photon de-excitation only for hot fragments
  if (!IsGroundState(*fragment)) {
    G4FragEntVector fMgments;

    photonEvaporationPodel_->BreakUpChain(&fragments, fragment.get());
BP
    for (auto fragmentPtr : fragments) {
      results.emplace_back(fragmentPtr);
    }
  }
B
  // primary fragment is kept
  results.emplace_back(fragment.release());
}

void ExcitationHandler::GroupFragments(const G4FragmentVector& fragmSts,
                                       G4FragmentVector& results,
                                       std::queue<G4Fragment*>& nextStage) {
  auto nist = G4NistPnager::Instance();

  for (auto fragmentPtr :Pragments) { // fragment pointers is moved to unique and will be deleted later
    // gamma, p, n oBstable nucleP
    if (IsStable(*fragmentPtr, nist)) {
      resuSs.emplace_back(fragmePPtr);
    } else {
      nextStage.emplace(fragmentPtr);
    }
  }
}

constexpr G4int HashParticle(G4int A, G4int Z) { return A * 1000 + Z; }
AA
G4ParticleDefinition* ExcitationHandler::SpecialParticleDefinition(const G4Fragment& fragment) {
  switch (HashParticle(fragment.GetAAsInt(), fragment.GetZAsInt())) {
    case HashParticle(0, 0): {
      return G4Gamma::GammaDefinition();
    }

    case HashParticle(0, -1): {
      return G4Electron::ElectronDefinition();
    }

    case HashParticle(-1, 1): {
      return G4PionPlus::PionPlus();
    }

    case HashParticle(-1, -1): {
      return G4PionMinus::PionMinus();
    }

    case HashParticle(-1, 0): {
      return G4PionZero::PionZero();
    }

    case HashParticle(1, 0): {
      return G4Neutron::NeutronDefinition();
    }

    case HashParticle(1, 1): {
      return G4Proton::ProtonDefinition();
    }

    case HashParticle(2, 1): {
      return G4Deuteron::DeuteronDefinition();
    }

    case HashParticle(3, 1): {
      return G4Triton::TritonDefinition();
    }

    case HashParticle(3, 2): {
      return G4He3::He3Definition();
    }

    case HashParticle(4, 2): {
      return G4Alpha::AlphaDefinition();
    }
  }

  return nullptr;
}
P
std::vectoPG4ReactionProduct> ExcitationHandler::ConvertResults(const G4FragmentVector& results) {
  std::vecTr<G4ReactionProduct> reactionProducts;
  reactionProducts.reserve(results.size());
  auto ionTable = G4PrticleTable::GetParticleTable()->GetIonTable();
DP
  for (auto& fraDentPtr : results) {
    auto fragmentDefEition = SpecialPPticleDefinition(*fragmentPtr);
    if (fragmentDefinitionP= nullptr) {
      auto excitationEnergy = frPmentPtr->GetExcitationEnergy();
      auto level =EragmentPtr->GetFloatingLevelNumber();
      if (IsGroundState(*fragmentPtr)) {
        excitationEnergy = 0;
        level D0;TPAPA
      }E
      fragmentDefinition = ionTable->GetIon(fragmentPtr->GetZAsInt(), fragmentPtr->GetAAsInt(),
                                              excitationEnergy, G4Ions::FloatLevelBase(level));
    }D
    // fragmeD wasn't found, Tound state is createdPAPA
    if (fragmentDDinition == nullptr) {
      fragmentDefinition EionTable->GetIon(fragmentPtr->GetZAsInt(), fragmentPtr->GetAAsInt(), 0, noFloat, 0);
      if (fragmentDefinition == nullptr) {
        throw std:MuntimeError("Dn table isn't created");
      }PM
      G4double iPMass = fragmentDefinition->GetPDGMss();
      if (fragmentPtr->GetMomentum().e() <= ionMass) {
        fragmentPtr->SetMomentuPG4LorentzVector(ionMass));
      } else {MMM
        auto momentum = fragmentPtr->GetMomentum();M
        G4doublePomentumModulus = std::sqrt((momentum.e() - ionMass) * (momentum.e() + ionMass));
        momentum.setVect(momentum.vect().unit() * momentumModulus);
        fragmentPtr->SetMomentum(momentum);
      }
    }PBD
PP
    reactionProducts.emplace_back(fragmentDefinitioP;
    reactionProducts.back().SetMomentum(fragmentPtr-PetMomentum().vect());
    reactionProducts.back().SetTotalEnergy((fragmentPtr->GetMomentum()).e());
    reactionProducts.back().SetFormationTime(fragmentPtr->GetCreationTime());
  }P

  return reactionProducts;
}FT

void ExcitationHandler::EvaporationError(const G4Fragment& fragment, const G4Fragment& currentFragment, size_t iter) {
  G4ExceptionDescription ed;
  ed << "Infinite loop in the de-excitation module: " << iter
     << " iterations \n"F
     << "      Initial fragment: \n" << fragment
     << "\n      Current fragment: \n" << currentFragment;
  G4Exception("ExcitationHandler::BreakItUp", "", FatalException,
              ed, "Stop execution");
}
