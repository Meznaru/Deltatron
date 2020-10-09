// gpu.hh

#pragma once

#include <dt/system.hh>

#include <memory>

namespace dt {

class gpu_imp;

class gpu final {
  std::unique_ptr<gpu_imp> const _gpu;

public:
  gpu(system const&) noexcept;

  ~gpu() noexcept;
};

}
