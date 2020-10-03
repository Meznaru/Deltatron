// gpu.hh

#pragma once

#include <dt/config.hh>

#include <memory>

namespace dt {

class gpu_imp;

class gpu final {
  std::unique_ptr<gpu_imp> const _gpu;

public:
  gpu(config const& cfg) noexcept;

  ~gpu() noexcept;
};

}
