// gpu.cc

#include <dt/gpu.hh>

#include <dt/gpu_imp.hh>

dt::gpu::gpu(system const& sys) noexcept
: _gpu(std::make_unique<gpu_imp>(sys)) {}

dt::gpu::~gpu() noexcept {}
