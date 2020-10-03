// deltatron.hh

#pragma once

#include <dt/config.hh>
#include <dt/gpu.hh>

namespace dt {

class deltatron final {
  config const _config;
//  gpu    const _gpu;

public:
  deltatron(int ac, char const** av, char const** ep);

  void run() const;
};

}
