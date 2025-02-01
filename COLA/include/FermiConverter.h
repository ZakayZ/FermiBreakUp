#pragma once

#include <COLA.hh>
#include <memory>

namespace fbu {
  class FermiBreakUp;
}

namespace cola {

  class FermiConverter final : public cola::VConverter {
  public:
    FermiConverter(std::unique_ptr<fbu::FermiBreakUp>&&);

    std::unique_ptr<cola::EventData> operator()(std::unique_ptr<cola::EventData>&& data) final;

  private:
    std::unique_ptr<fbu::FermiBreakUp> model_;
  };

} // namespace cola
