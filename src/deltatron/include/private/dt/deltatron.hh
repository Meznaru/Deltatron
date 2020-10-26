// deltatron.hh

#pragma once

#include <dt/system.hh>

namespace dt {

class deltatron final {
  system const _system;

public:
  deltatron(int ac, char const** av, char const** ep);

  void run() const;
};

}
