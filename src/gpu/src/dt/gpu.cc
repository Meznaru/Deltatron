// gpu.cc

#include <dt/gpu.hh>

#include <dt/gpu_imp.hh>

dt::gpu::gpu(config const& cfg) noexcept
: _gpu(std::make_unique<gpu_imp>(cfg)) {}

dt::gpu::~gpu() noexcept {}
