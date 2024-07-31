#pragma once

class ExcitationHandler;

namespace cola {

  class G4HandlerConverter final : public cola::VConverter {
  public:
    G4HandlerConverter(std::unique_ptr<ExcitationHandler>&& model);

    std::unique_ptr<cola::EventData> operator()(std::unique_ptr<cola::EventData>&& data) override final;

  private:
    std::unique_ptr<ExcitationHandler> model_;
  };

}  // namespace cola
