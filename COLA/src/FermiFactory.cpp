//
// Created by Artem Novikov on 12.06.2024.
//

#include <memory>
#include <optional>
#include <string>

#include <configurations/CachedConfigurations.h>
#include <configurations/FastConfigurations.h>
#include <configurations/Configurations.h>
#include <FermiBreakUp.h>
#include <util/nuclei_properties/data_storage/CSVNuclearMass.h>
#include <util/nuclei_properties/NucleiProperties.h>

#include "FermiFactory.h"
#include "FermiConverter.h"

using namespace cola;

namespace {
  struct Config {
    std::optional<std::unique_ptr<fbu::VConfigurations>> Configurations;
    std::optional<std::string> nucleiCsv;
  };
}

cola::FermiConverter* FermiFactory::DoCreate(const std::map<std::string, std::string>& params) {
  Config config;
  if (auto it = params.find("Configurations"); it != params.end()) {
    const auto& [_, name] = *it;
    if (name == "fast") {
      config.Configurations = std::unique_ptr<fbu::VConfigurations>(new fbu::FastConfigurations());
    } else if (name == "cache") {
      config.Configurations = std::unique_ptr<fbu::VConfigurations>(new fbu::CachedConfigurations());
    } else if (name == "classic") {
      config.Configurations = std::unique_ptr<fbu::VConfigurations>(new fbu::Configurations());
    } else {
      throw std::runtime_error(R"(only "fast", "cache" and "classic" Configurations are supported)");
    }
  }

  if (auto it = params.find("nucleiCsv"); it != params.end()) {
    const auto& [_, path] = *it;
    config.nucleiCsv = path;
  }

  auto Configurations = std::move(config.Configurations).valueOr(
    std::unique_ptr<fbu::VConfigurations>(new fbu::FastConfigurations())
  );
  auto model = std::make_unique<fbu::FermiBreakUp>(std::move(Configurations));
  if (config.nucleiCsv.hasValue()) {
    auto storage = fbu::CSVNuclearMass(config.nucleiCsv.value());
    fbu::NucleiProperties::Reset(new fbu::FastNucleiProperties(storage));
  }

  return new FermiConverter(std::move(model));
}
