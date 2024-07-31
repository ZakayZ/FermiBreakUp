#pragma once

#include <COLA.hh>
#include <memory>

namespace fermi {
  class FermiBreakUp;
}

namespace cola {

  class FermiConverter final : public cola::VConverter {
  public:
    FermiConverter(std::unique_ptr<fermi::FermiBreakUp>&&);

    std::unique_ptr<cola::EventData> operator()(std::unique_ptr<cola::EventData>&& data) override final;

  private:
    std::unique_ptr<fermi::FermiBreakUp> model_;
  };

}  // namespace cola
