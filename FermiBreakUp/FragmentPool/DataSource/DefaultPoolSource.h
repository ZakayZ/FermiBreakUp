//
// Created by Artem Novikov on 17.02.2024.
//

#ifndef HANDLER_MYFERMIBREAKUP_FRAGMENTPOOL_DATASOURCE_DEFAULTPOOLSOURCE_H_
#define HANDLER_MYFERMIBREAKUP_FRAGMENTPOOL_DATASOURCE_DEFAULTPOOLSOURCE_H_

#include <vector>

#include "FragmentPool/Fragments/Fragment.h"

namespace fermi {

  class DefaultPoolSource {
  private:
    using Container = std::vector<const Fragment*>;

  public:
    DefaultPoolSource();

    ~DefaultPoolSource() = default;

    Container::iterator begin() { return fragments_.begin(); }

    Container::const_iterator begin() const { return fragments_.begin(); }

    Container::const_iterator cbegin() const { return fragments_.cbegin(); }

    Container::iterator end() { return fragments_.end(); }

    Container::const_iterator end() const { return fragments_.end(); }

    Container::const_iterator cend() const { return fragments_.cend(); }

  private:
    Container fragments_;
  };

} // namespace fermi

#endif //HANDLER_MYFERMIBREAKUP_FRAGMENTPOOL_DATASOURCE_DEFAULTPOOLSOURCE_H_
