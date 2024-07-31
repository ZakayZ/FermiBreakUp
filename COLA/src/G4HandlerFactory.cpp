#include <memory>
#include <optional>
#include <string>

#include <Randomize.hh>
#include <ExcitationHandler.h>

#include "G4HandlerFactory.h"
#include "G4HandlerConverter.h"

using namespace cola;

namespace {
  bool EndsWith(const std::string& s, const std::string& suffix) {
    return suffix.size() < s.size() && s.substr(s.size() - suffix.size()) == suffix;
  }

  double StodWithFactor(const std::string& value) {
    auto num = std::stod(value);
    if (EndsWith(value, "eV")) {
      return num * CLHEP::eV;
    }

    if (EndsWith(value, "MeV")) {
      return num * CLHEP::MeV;
    }

    if (EndsWith(value, "keV")) {
      return num * CLHEP::keV;
    }

    if (EndsWith(value, "GeV")) {
      return num * CLHEP::GeV;
    }

    return num;
  }

  struct Config {
    Config(const std::map<std::string, std::string>& params) {
      if (auto it = params.find("A"); it != params.end()) {
        const auto& [_, value] = *it;
        A = std::stoul(value);
      }

      if (auto it = params.find("Z"); it != params.end()) {
        const auto& [_, value] = *it;
        Z = std::stoul(value);
      }

      if (auto it = params.find("lower_mf_threshold"); it != params.end()) {
        const auto& [_, value] = *it;
        lower_mf_threshold = StodWithFactor(value);
      }

      if (auto it = params.find("upper_mf_threshold"); it != params.end()) {
        const auto& [_, value] = *it;
        upper_mf_threshold = StodWithFactor(value);
      }

      if (auto it = params.find("stable_threshold"); it != params.end()) {
        const auto& [_, value] = *it;
        stable_threshold = StodWithFactor(value);
      }
    }

    std::optional<int> A;
    std::optional<int> Z;
    std::optional<double> stable_threshold;
    std::optional<double> lower_mf_threshold;
    std::optional<double> upper_mf_threshold;
  };
}

cola::G4HandlerConverter* G4HandlerFactory::DoCreate(const std::map<std::string, std::string>& params) {
  auto config = Config(params);

  auto model = std::make_unique<ExcitationHandler>();

  if (config.stable_threshold.has_value()) {
    model->SetStableThreshold(*config.stable_threshold);
  }

  model->SetFermiBreakUpCondition([max_A=config.A.value_or(19), max_Z=config.Z.value_or(9)] (const G4Fragment& fragment) {
    return fragment.GetZ_asInt() < max_Z && fragment.GetA_asInt() < max_A;
  });

  model->SetMultiFragmentationCondition([
      max_A=config.A.value_or(19),
      max_Z=config.Z.value_or(9),
      lower_bound_transition_MF=config.lower_mf_threshold.value_or(3 * CLHEP::MeV),
      upper_bound_transition_MF=config.upper_mf_threshold.value_or(5 * CLHEP::MeV)
    ] (const G4Fragment& fragment) {
      auto A = fragment.GetA_asInt();
      auto Z = fragment.GetZ_asInt();
      auto Ex = fragment.GetExcitationEnergy();
      if (A < max_A && Z < max_Z) {
        return false;
      }
      G4double aE = 1 / (2. * (upper_bound_transition_MF - lower_bound_transition_MF));
      G4double E0 = (upper_bound_transition_MF + lower_bound_transition_MF) / 2.;
      G4double w = G4RandFlat::shoot();
      G4double transF = 0.5 * std::tanh((Ex / A - E0) / aE) + 0.5;

      if (Ex < lower_bound_transition_MF * A) { return false; }

      if (w < transF && Ex < upper_bound_transition_MF * A) { return true; }

      if (w > transF && Ex < upper_bound_transition_MF * A) { return false; }

      if (Ex > upper_bound_transition_MF * A) { return true; }

      return false;
  });

  return new G4HandlerConverter(std::move(model));
}
