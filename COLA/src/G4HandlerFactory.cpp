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

      if (auto it = params.find("lowerMfThreshold"); it != params.end()) {
        const auto& [_, value] = *it;
        lowerMfThreshold = StodWithFactor(value);
      }

      if (auto it = params.find("upperMfThreshold"); it != params.end()) {
        const auto& [_, value] = *it;
        upperMfThreshold = StodWithFactor(value);
      }

      if (auto it = params.find("stableThreshold"); it != params.end()) {
        const auto& [_, value] = *it;
        stableThreshold = StodWithFactor(value);
      }
    }

    std::optional<int> A;
    std::optional<int> Z;
    std::optional<double> stableThreshold;
    std::optional<double> lowerMfThreshold;
    std::optional<double> upperMfThreshold;
  };
}

cola::G4HandlerConverter* G4HandlerFactory::DoCreate(const std::map<std::string, std::string>& params) {
  auto config = Config(params);

  auto model = std::make_unique<ExcitationHandler>();

  if (config.stableThreshold.hasValue()) {
    model->SetStableThreshold(*config.stableThreshold);
  }

  model->SetFermiBreakUpCondition([maxA=config.A.valueOr(19), maxZ=config.Z.valueOr(9)] (const G4Fragment& fragment) {
    return fragment.GetZAsInt() < maxZ && fragment.GetAAsInt() < maxA;
  });

  model->SetMultiFragmentationCondition([
      maxA=config.A.valueOr(19),
      maxZ=config.Z.valueOr(9),
      lowerBoundTransitionMF=config.lowerMfThreshold.valueOr(3 * CLHEP::MeV),
      upperBoundTransitionMF=config.upperMfThreshold.valueOr(5 * CLHEP::MeV)
    ] (const G4Fragment& fragment) {
      auto A = fragment.GetAAsInt();
      auto Z = fragment.GetZAsInt();
      auto Ex = fragment.GetExcitationEnergy();
      if (A < maxA && Z < maxZ) {
        return false;
      }
      G4double aE = 1 / (2. * (upperBoundTransitionMF - lowerBoundTransitionMF));
      G4double E0 = (upperBoundTransitionMF + lowerBoundTransitionMF) / 2.;
      G4double w = G4RandFlat::shoot();
      G4double transF = 0.5 * std::tanh((Ex / A - E0) / aE) + 0.5;

      if (Ex < lowerBoundTransitionMF * A) { return false; }

      if (w < transF && Ex < upperBoundTransitionMF * A) { return true; }

      if (w > transF && Ex < upperBoundTransitionMF * A) { return false; }

      if (Ex > upperBoundTransitionMF * A) { return true; }

      return false;
  });

  return new G4HandlerConverter(std::move(model));
}
