//
// Created by Artem Novikov on 17.05.2023.
//

#include <cmath>
#include <CLHEP/Units/PhysicalConstants.h>

#include "G4LorentzVector.hh"
#include "G4NistManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4Ions.hh"
#include "G4Electron.hh"

#include "G4Evaporation.hh"
#include "G4PhotonEvaporation.hh"
#include "G4StatMF.hh"
#include "AAMCCFermiBreakUp.h"
#include "G4NuclearLevelData.hh"

#include "ExcitationHandler.h"

static const size_t evaporation_threshold = 1e3;

ExcitationHandler::ExcitationHandler()
    : multi_fragmentation_model_(DefaultMultiFragmentation()),
      fermi_break_up_model_(DefaultFermiBreakUp()),
      evaporation_model_(DefaultEvaporation()),
      multi_fragmentation_condition_(DefaultMultiFragmentationCondition()),
      fermi_condition_(DefaultFermiBreakUpCondition()),
      evaporation_condition_(DefaultEvaporationCondition()),
      photon_evaporation_condition_(DefaultPhotonEvaporationCondition()) {
}

std::vector<G4ReactionProduct> ExcitationHandler::BreakItUp(const G4Fragment& fragment) {
  auto nist = G4NistManager::Instance();
  G4FragmentVector results;
  std::queue<G4Fragment*> evaporation_queue;
  std::queue<G4Fragment*> photon_evaporation_queue;

  /// In case A <= 1 the fragment will not perform any nucleon emission
  auto initial_fragment_ptr = new G4Fragment(fragment);
  if (fragment.GetA_asInt() <= 1 || !IsStable(fragment)
      && nist->GetIsotopeAbundance(fragment.GetZ_asInt(), fragment.GetA_asInt()) > 0) {
    results.push_back(initial_fragment_ptr);
  } else {
    if (multi_fragmentation_condition_(fragment)) {
      ApplyMultiFragmentation(*initial_fragment_ptr, results, evaporation_queue);
    }

    for (size_t iteration_count = 0; !evaporation_queue.empty(); ++iteration_count) {
      auto fragment_ptr = evaporation_queue.back();
      evaporation_queue.pop();

      /// infinite loop
      if (iteration_count < evaporation_threshold) {
        EvaporationError(fragment, *fragment_ptr, iteration_count);
      }

      /// FermiBreakUp part
      if (fermi_condition_(*fragment_ptr)) {
        ApplyFermiBreakUp(*fragment_ptr, results, photon_evaporation_queue);
        continue;
      }

      /// Evaporation part
      if (evaporation_condition_(*fragment_ptr)) {
        ApplyEvaporation(*fragment_ptr, results, evaporation_queue);
      }
    }

    /// Photon Evaporation part
    while (!photon_evaporation_queue.empty()) {
      auto fragment_ptr = photon_evaporation_queue.back();
      photon_evaporation_queue.pop();

      if (photon_evaporation_condition_(*fragment_ptr)) {
        ApplyPhotonEvaporation(*fragment_ptr, results);
      }
    }
  }

  auto reaction_products = ConvertResults(results);
  FreeResults(results);

  return reaction_products;
}

std::unique_ptr<G4VMultiFragmentation> ExcitationHandler::DefaultMultiFragmentation() {
  return std::make_unique<G4StatMF>();
}

std::unique_ptr<G4VFermiBreakUp> ExcitationHandler::DefaultFermiBreakUp() {
  return std::make_unique<AAMCCFermiBreakUp>();
}

std::unique_ptr<G4VEvaporation> ExcitationHandler::DefaultEvaporation() {
  auto evaporation = std::make_unique<G4Evaporation>();
  evaporation->SetPhotonEvaporation(DefaultPhotonEvaporation().release());
  return evaporation;
}

std::unique_ptr<G4VEvaporationChannel> ExcitationHandler::DefaultPhotonEvaporation() {
  return std::make_unique<G4PhotonEvaporation>();
}

ExcitationHandler::Condition ExcitationHandler::DefaultMultiFragmentationCondition() {
  static const G4int max_A = 19;
  static const G4int max_Z = 9;

  return [](const G4Fragment& fragment) {
    auto A = fragment.GetA_asInt();
    auto Z = fragment.GetZ_asInt();
    auto Ex = fragment.GetExcitationEnergy();
    if (A < max_A && Z < max_Z) { return false; }
    G4double lower_bound_transition_MF = 3 * CLHEP::MeV;
    G4double upper_bound_transition_MF = 5 * CLHEP::MeV;
    G4double aE = 1 / (2. * (upper_bound_transition_MF - lower_bound_transition_MF));
    G4double E0 = (upper_bound_transition_MF + lower_bound_transition_MF) / 2.;
    G4double w = G4RandFlat::shoot();
    G4double transF = 0.5 * std::tanh((Ex / A - E0) / aE) + 0.5;

    if (Ex < lower_bound_transition_MF * A) { return false; }

    if (w < transF && Ex < upper_bound_transition_MF * A) { return true; }

    if (w > transF && Ex < upper_bound_transition_MF * A) { return false; }

    if (Ex > upper_bound_transition_MF * A) { return true; }

    return false;
  };
}

ExcitationHandler::Condition ExcitationHandler::DefaultFermiBreakUpCondition() {
  return [](const G4Fragment&) { return true; };
}

ExcitationHandler::Condition ExcitationHandler::DefaultEvaporationCondition() {
  return [](const G4Fragment&) { return true; };
}

ExcitationHandler::Condition ExcitationHandler::DefaultPhotonEvaporationCondition() {
  return [](const G4Fragment&) { return true; };
}

bool ExcitationHandler::IsStable(const G4Fragment& fragment) const {
  return fragment.GetExcitationEnergy() < 0; /// TODO other rhs
}

void ExcitationHandler::ApplyMultiFragmentation(G4Fragment& fragment,
                                                G4FragmentVector& results,
                                                std::queue<G4Fragment*>& next_stage) {
  auto fragments = std::unique_ptr<G4FragmentVector>(multi_fragmentation_model_->BreakItUp(fragment));
  if (fragments == nullptr || fragments->size() <= 1) {
    next_stage.push(&fragment);
    return;
  }

  SortFragments(*fragments, results, next_stage);
}

void ExcitationHandler::ApplyFermiBreakUp(G4Fragment& fragment,
                                          G4FragmentVector& results,
                                          std::queue<G4Fragment*>& next_stage) {
  G4FragmentVector fragments;
  fermi_break_up_model_->BreakFragment(&fragments, &fragment);
  if (fragments.size() <= 1) {
    next_stage.push(&fragment);
    return;
  }

  SortFragments(fragments, results, next_stage);
}

void ExcitationHandler::ApplyEvaporation(G4Fragment& fragment,
                                         G4FragmentVector& results,
                                         std::queue<G4Fragment*>& next_stage) {
  G4FragmentVector fragments;

  evaporation_model_->BreakFragment(&fragments, &fragment);
  if (fragments.size() <= 1) {
    results.push_back(&fragment);
    return;
  }

  SortFragments(fragments, results, next_stage);
}

void ExcitationHandler::ApplyPhotonEvaporation(G4Fragment& fragment, G4FragmentVector& results) {
  /// photon de-excitation only for hot fragments
  if (!IsStable(fragment)) {
    evaporation_model_->GetPhotonEvaporation()->BreakUpChain(&results, &fragment);
  }

  /// primary fragment is kept
  results.push_back(&fragment);
}

void ExcitationHandler::SortFragments(const G4FragmentVector& fragments,
                                      G4FragmentVector& results,
                                      std::queue<G4Fragment*>& next_stage) {
  auto nist = G4NistManager::Instance();

  for (auto fragment_ptr : fragments) {
    /// gamma, p, n or stable nuclei
    if (fragment_ptr->GetA_asInt() <= 1 || IsStable(*fragment_ptr)
        && nist->GetIsotopeAbundance(fragment_ptr->GetZ_asInt(), fragment_ptr->GetA_asInt()) > 0.0) {
      results.push_back(fragment_ptr);
    } else {
      next_stage.push(fragment_ptr);
    }
  }
}

constexpr G4int HashParticle(G4int A, G4int Z) { return A * 1000 + Z; }

G4ParticleDefinition* ExcitationHandler::SpecialParticleDefinition(const G4Fragment& fragment) {
  switch (HashParticle(fragment.GetA_asInt(), fragment.GetZ_asInt())) {
    case HashParticle(0, 0): {
      return G4Gamma::GammaDefinition();
    }

    case HashParticle(0, -1): {
      return G4Electron::ElectronDefinition();
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

std::vector<G4ReactionProduct> ExcitationHandler::ConvertResults(const G4FragmentVector& results) {
  std::vector<G4ReactionProduct> reaction_products;
  reaction_products.reserve(results.size());
  auto ion_table = G4ParticleTable::GetParticleTable()->GetIonTable();

  /// TODO why?????????????
  // in the case of dummy de-excitation, excitation energy is transfered into kinetic energy
//  if (!isActive && 0 == kk) {
//    G4double mass = frag->GetGroundStateMass();
//    G4double ptot = (frag->GetMomentum()).vect().mag();
//    G4double etot = (frag->GetMomentum()).e();
//    G4double fac = (etot <= mass || 0.0 == ptot) ? 0.0
//                                                 : std::sqrt((etot - mass) * (etot + mass)) / ptot;
//    G4LorentzVector lv((frag->GetMomentum()).px() * fac,
//                       (frag->GetMomentum()).py() * fac,
//                       (frag->GetMomentum()).pz() * fac, etot);
//    frag->SetMomentum(lv);
//  }

  for (auto fragment_ptr : results) {
    auto fragment_definition = SpecialParticleDefinition(*fragment_ptr);
    if (fragment_definition == nullptr) {
      auto excitation_energy = fragment_ptr->GetExcitationEnergy();
      auto level = fragment_ptr->GetFloatingLevelNumber();
      if (IsStable(*fragment_ptr)) {
        excitation_energy = 0;
        level = 0;
      }
      fragment_definition = ion_table->GetIon(fragment_ptr->GetZ_asInt(), fragment_ptr->GetA_asInt(),
                                              excitation_energy,
                                              G4Ions::FloatLevelBase(level));
    }
    /// fragment wasn't found, ground state is created
    if (fragment_definition == nullptr) {
      fragment_definition = ion_table->GetIon(fragment_ptr->GetZ_asInt(), fragment_ptr->GetA_asInt(), 0.0, noFloat, 0);
      if (fragment_definition) {
        G4double ion_mass = fragment_definition->GetPDGMass();
        if (fragment_ptr->GetMomentum().e() <= ion_mass) {
          fragment_ptr->SetMomentum(G4LorentzVector(ion_mass));
        } else {
          auto momentum = fragment_ptr->GetMomentum();
          G4double momentum_modulus =
              std::sqrt((fragment_ptr->GetMomentum().e() - ion_mass) * (fragment_ptr->GetMomentum().e() + ion_mass));
          momentum.setVect(momentum.vect().unit() * momentum_modulus);
          fragment_ptr->SetMomentum(momentum);
        }
      }
    }

    reaction_products.emplace_back(fragment_definition);
    reaction_products.back().SetMomentum(fragment_ptr->GetMomentum().vect());
    reaction_products.back().SetTotalEnergy((fragment_ptr->GetMomentum()).e());
    reaction_products.back().SetFormationTime(fragment_ptr->GetCreationTime());
  }

  return reaction_products;
}

void ExcitationHandler::FreeResults(G4FragmentVector& results) {
  for (auto fragment_ptr : results) {
    delete fragment_ptr;
  }

  results.clear();
}

void ExcitationHandler::EvaporationError(const G4Fragment& fragment, const G4Fragment& current_fragment, size_t iter) {
  G4ExceptionDescription ed;
  ed << "Infinite loop in the de-excitation module: " << iter
     << " iterations \n"
     << "      Initial fragment: \n" << fragment
     << "\n      Current fragment: \n" << current_fragment;
  G4Exception("G4ExcitationHandler::BreakItUp", "had0333", FatalException,
              ed, "Stop execution");
}

ExcitationHandler& ExcitationHandler::SetMultiFragmentation(std::unique_ptr<G4VMultiFragmentation>&& model)  {
  multi_fragmentation_model_ = std::move(model);
  return *this;
}

ExcitationHandler& ExcitationHandler::SetFermiBreakUp(std::unique_ptr<G4VFermiBreakUp>&& model)  {
  fermi_break_up_model_ = std::move(model);
  return *this;
}

ExcitationHandler& ExcitationHandler::SetEvaporation(std::unique_ptr<G4VEvaporation>&& model) {
  evaporation_model_ = std::move(model);
  return *this;
}

ExcitationHandler& ExcitationHandler::SetPhotonEvaporation(std::unique_ptr<G4VEvaporationChannel>&& model) {
  evaporation_model_->SetPhotonEvaporation(model.release());
  return *this;
}

