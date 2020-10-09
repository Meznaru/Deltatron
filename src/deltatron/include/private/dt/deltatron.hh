// deltatron.hh

#pragma once

#include <dt/system.hh>
#include <dt/gpu.hh>

namespace dt {

class deltatron final {
  system const _system;
//  gpu    const _gpu;

public:
  deltatron(int ac, char const** av, char const** ep);

  void run() const;
};

}
