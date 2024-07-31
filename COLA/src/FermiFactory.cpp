//
// Created by Artem Novikov on 12.06.2024.
//

#include <memory>
#include <optional>
#include <string>

#include <Configurations/CachedConfigurations.h>
#include <Configurations/FastConfigurations.h>
#include <Configurations/Configurations.h>
#include <FermiBreakUp.h>
#include <Utilities/NucleiProperties/DataStorage/CSVNuclearMass.h>
#include <Utilities/NucleiProperties/NucleiProperties.h>

#include "FermiFactory.h"
#include "FermiConverter.h"

using namespace cola;

namespace {
  struct Config {
    std::optional<std::unique_ptr<fermi::VConfigurations>> configurations;
    std::optional<std::string> nuclei_csv;
  };
}

cola::FermiConverter* FermiFactory::DoCreate(const std::map<std::string, std::string>& params) {
  Config config;
  if (auto it = params.find("configurations"); it != params.end()) {
    const auto& [_, name] = *it;
    if (name == "fast") {
      config.configurations = std::unique_ptr<fermi::VConfigurations>(new fermi::FastConfigurations());
    } else if (name == "cache") {
      config.configurations = std::unique_ptr<fermi::VConfigurations>(new fermi::CachedConfigurations());
    } else if (name == "classic") {
      config.configurations = std::unique_ptr<fermi::VConfigurations>(new fermi::Configurations());
    } else {
      throw std::runtime_error(R"(only "fast", "cache" and "classic" configurations are supported)");
    }
  }

  if (auto it = params.find("nuclei_csv"); it != params.end()) {
    const auto& [_, path] = *it;
    config.nuclei_csv = path;
  }

  auto configurations = std::move(config.configurations).value_or(
    std::unique_ptr<fermi::VConfigurations>(new fermi::FastConfigurations())
  );
  auto model = std::make_unique<fermi::FermiBreakUp>(std::move(configurations));
  if (config.nuclei_csv.has_value()) {
    auto storage = properties::CSVNuclearMass(config.nuclei_csv.value());
    properties::NucleiProperties::Reset(new properties::FastNucleiProperties(storage));
  }

  return new FermiConverter(std::move(model));
}
