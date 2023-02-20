//
// Created by Artem Novikov on 21.02.2023.
//

#ifndef FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_
#define FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_

#include "FermiParticle.h"
#include "FermiConfigurations.h"

using ParticleSplit = std::vector<FermiParticle>;

class FermiBreakUp {
 public:
  FermiBreakUp() = default;

  FermiBreakUp(const FermiBreakUp&) = delete;

  FermiBreakUp& operator=(const FermiBreakUp&) = delete;

  ParticleSplit BreakItUp(const FermiParticle& nucleus) const;

  ~FermiBreakUp() = default;
 private:
  static ParticleSplit ConvertToParticles(const FermiParticle& source_nucleus, const FragmentSplit& split);
};

#endif //FERMIBREAKUP_MYFERMIBREAKUP_FERMIBREAKUP_H_
