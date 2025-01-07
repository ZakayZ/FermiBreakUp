//
// Created by Artem Novikov on 17.05.2023.
//

#ifndef FERMIBREAKUPHANDLEREXCITATIONHANDLERH_
#define FERMIBREAKUPHANDLEREXCITATIONHANDLERH_

#include <functional>
#include <memory>
#include <vector>
#include <queue>

#include "G4Fragment.hh"
#include "G4ReactionProductVector.hh"
#include "G4IonTable.hh"
#include "G4DeexPrecoParameters.hh"
#include "G4Fragment.hh"
#include "G4NistManager.hh"

#include "G4VMultiFragmentation.hh"
#include "G4VEvaporation.hh"
#include "G4VFermiBreakUp.hh"

class ExcitationHandler {
 public:
  using Condition = std::function<bool(const G4Fragment&)>;

  ExcitationHandler();

  ExcitationHandler(const ExcitationHandler&) = delete;

  ExcitationHandler(ExcitationHandler&&) = default;

  ~ExcitationHandler();

  ExcitationHandler& operator=(const ExcitationHandler&) = delete;

  ExcitationHandler& operator=(ExcitationHandler&&) = default;

  std::vector<G4ReactionProduct> BreakItUp(const G4Fragment& fragment);

  // parameters setters
  ExcitationHandler& SetMultiFragmentation(std::unique_ptr<G4VMultiFragmentation>&& model = DefaultMultiFragmentation()) {
    multiFragmentationModel_ = std::move(model);
    return *this;
  }

  ExcitationHandler& SetFermiBreakUp(std::unique_ptr<G4VFermiBreakUp>&& model = DefaultFermiBreakUp(),
                                     bool setModels = true) {
    fermiBreakUpModel_ = std::move(model);
    if (setModels) {
      evaporationModel_->SetFermiBreakUp(fermiBreakUpModel_.get());
    }
    return *this;
  }

  ExcitationHandler& SetEvaporation(std::unique_ptr<G4VEvaporation>&& model = DefaultEvaporation(),
                                    bool setModels = true) {
    evaporationModel_ = std::move(model);
    if (setModels) {
      evaporationModel_->SetPhotonEvaporation(photonEvaporationModel_.get());
      evaporationModel_->SetFermiBreakUp(fermiBreakUpModel_.get());
    }
    return *this;
  }

  ExcitationHandler& SetPhotonEvaporation(std::unique_ptr<G4VEvaporationChannel>&& model = DefaultPhotonEvaporation(),
                                          bool setModels = true) {
    photonEvaporationModel_ = std::move(model);
    if (setModels) {
      evaporationModel_->SetPhotonEvaporation(photonEvaporationModel_.get());
    }
    return *this;
  }

  template <class F>
  ExcitationHandler& SetMultiFragmentationCondition(F&& f) {
    multiFragmentationCondition_ = std::forward<F>(f);
    return *this;
  }

  ExcitationHandler& SetMultiFragmentationCondition() {
    return SetMultiFragmentationCondition(DefaultMultiFragmentationCondition());
  }

  template <class F>
  ExcitationHandler& SetFermiBreakUpCondition(F&& f) {
    fermiCondition_ = std::forward<F>(f);
    return *this;
  }

  ExcitationHandler& SetFermiBreakUpCondition() {
    return SetFermiBreakUpCondition(DefaultFermiBreakUpCondition());
  }

  template <class F>
  ExcitationHandler& SetEvaporationCondition(F&& f) {
    evaporationCondition_ = std::forward<F>(f);
    return *this;
  }

  ExcitationHandler& SetEvaporationCondition() {
    return SetEvaporationCondition(DefaultEvaporationCondition());
  }

  template <class F>
  ExcitationHandler& SetPhotonEvaporationCondition(F&& f) {
    photonEvaporationCondition_ = std::forward<F>(f);
    return *this;
  }

  ExcitationHandler& SetPhotonEvaporationCondition() {
    return SetPhotonEvaporationCondition(DefaultPhotonEvaporationCondition());
  }

  ExcitationHandler& SetStableThreshold(Float threshold) {
    stableThreshold_ = threshold;
    return *this;
  }

  // parameters getters
  std::unique_ptr<G4VMultiFragmentation>& GetMultiFragmentation() { return multiFragmentationModel_; }

  const std::unique_ptr<G4VMultiFragmentation>& GetMultiFragmentation() const { return multiFragmentationModel_; }

  std::unique_ptr<G4VFermiBreakUp>& GetFermiBreakUp() { return fermiBreakUpModel_; }

  const std::unique_ptr<G4VFermiBreakUp>& GetFermiBreakUp() const { return fermiBreakUpModel_; }

  std::unique_ptr<G4VEvaporation>& GetEvaporation() { return evaporationModel_; }

  const std::unique_ptr<G4VEvaporation>& GetEvaporation() const { return evaporationModel_; }

  Condition& GetMultiFragmentationCondition() { return multiFragmentationCondition_; }

  const Condition& GetMultiFragmentationCondition() const { return multiFragmentationCondition_; }

  Condition& GetFermiBreakUpCondition() { return fermiCondition_; }

  const Condition& GetFermiBreakUpCondition() const { return fermiCondition_; }

  Condition& GetEvaporationCondition() { return evaporationCondition_; }

  const Condition& GetEvaporationCondition() const { return evaporationCondition_; }

  Condition& GetPhotonEvaporationCondition() { return photonEvaporationCondition_; }

  const Condition& GetPhotonEvaporationCondition() const { return photonEvaporationCondition_; }

  Float GetStableThreshold() const { return stableThreshold_; }

 protected:
  static G4ParticleDefinition* SpecialParticleDefinition(const G4Fragment& fragment);

  static void EvaporationError(const G4Fragment& fragment, const G4Fragment& currentFragment, size_t iter);

  // default models and conditions
  static std::unique_ptr<G4VMultiFragmentation> DefaultMultiFragmentation();

  static std::unique_ptr<G4VFermiBreakUp> DefaultFermiBreakUp();

  static std::unique_ptr<G4VEvaporation> DefaultEvaporation();

  static std::unique_ptr<G4VEvaporationChannel> DefaultPhotonEvaporation();

  static Condition DefaultMultiFragmentationCondition();

  static Condition DefaultFermiBreakUpCondition();

  static Condition DefaultEvaporationCondition();

  static Condition DefaultPhotonEvaporationCondition();

  static void CleanUp(G4FragmentVector& v, std::queue<G4Fragment*>& q1, std::queue<G4Fragment*>& q2);

  bool IsGroundState(const G4Fragment& fragment) const;

  bool IsStable(const G4Fragment& fragment, const G4NistManager* nist) const;

  void ApplyMultiFragmentation(std::unique_ptr<G4Fragment> fragment, G4FragmentVector& results,
                               std::queue<G4Fragment*>& nextStage);

  void ApplyFermiBreakUp(std::unique_ptr<G4Fragment> fragment, G4FragmentVector& results,
                         std::queue<G4Fragment*>& nextStage);

  void ApplyEvaporation(std::unique_ptr<G4Fragment> fragment, G4FragmentVector& results,
                        std::queue<G4Fragment*>& nextStage);

  void ApplyPhotonEvaporation(std::unique_ptr<G4Fragment> fragment, G4FragmentVector& results);

  void GroupFragments(const G4FragmentVector& fragments, G4FragmentVector& results,
                      std::queue<G4Fragment*>& nextStage);

  std::vector<G4ReactionProduct> ConvertResults(const G4FragmentVector& results);

  std::unique_ptr<G4VMultiFragmentation> multiFragmentationModel_;
  std::unique_ptr<G4VFermiBreakUp> fermiBreakUpModel_;
  std::unique_ptr<G4VEvaporationChannel> photonEvaporationModel_;
  std::unique_ptr<G4VEvaporation> evaporationModel_;

  Condition multiFragmentationCondition_;
  Condition fermiCondition_;
  Condition photonEvaporationCondition_;
  Condition evaporationCondition_;

  Float stableThreshold_ = 0;

  static const size_t EvaporationIterationThreshold;

  static const char* ErrorNoModel;
};

#endif //FERMIBREAKUPHANDLEREXCITATIONHANDLERH_
