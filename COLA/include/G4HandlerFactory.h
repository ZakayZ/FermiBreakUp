#pragma once

#include <COLA.hh>

#include "G4HandlerConverter.h"

namespace cola {

  class G4HandlerFactory final : public cola::VFactory {
  public:
    cola::VFilter* create(const std::map<std::string, std::string>& params) final {
      return DoCreate(params);
    }

  private:
    cola::G4HandlerConverter* DoCreate(const std::map<std::string, std::string>& params);
  };

} // namespace cola
