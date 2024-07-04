//
// Created by Artem Novikov on 12.06.2024.
//

#ifndef RUNNER_COLA_INCLUDE_FERMIFACTORY_H_
#define RUNNER_COLA_INCLUDE_FERMIFACTORY_H_

#include <COLA.hh>
#include <string>

namespace cola {

class FermiFactory final : public cola::VFactory {
 public:
  cola::VFilter* create(const std::string) override final;

};

}  // namespace cola

#endif //RUNNER_COLA_INCLUDE_FERMIFACTORY_H_
