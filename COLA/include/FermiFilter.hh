//
// Created by Artem Novikov on 12.06.2024.
//

#ifndef RUNNER_COLA_INCLUDE_FERMIFILTER_H_
#define RUNNER_COLA_INCLUDE_FERMIFILTER_H_

#include <COLA.hh>

#include "FermiBreakUp.h"

namespace cola {

class FermiConverter final : public cola::VConverter {
 public:
  std::unique_ptr<cola::EventData> operator()(std::unique_ptr<cola::EventData> data) override final;

 private:
  fermi::FermiBreakUp model_;
};

}  // namespace cola

#endif //RUNNER_COLA_INCLUDE_FERMIFILTER_H_
