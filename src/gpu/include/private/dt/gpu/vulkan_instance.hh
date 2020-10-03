// vulkan_instance.hh

#pragma once

#include <dt/gpu/vulkan/vulkan.hh>

#include <stdexcept>

#include <cstdint>

namespace dt {

class vk_instance final {
  VkApplicationInfo    const  _ai;
  VkInstanceCreateInfo const  _ci;
  VkInstance           const  _inst;

public:
  vk_instance()
  : _ai(_vk_app_info()),
    _ci(_vk_create_info()),
    _inst(_vk_instance()) { }

  ~vk_instance() noexcept {
    vkDestroyInstance(_inst, nullptr);
  }

  constexpr VkInstance const* operator->() const noexcept { return &_inst; }

  constexpr VkInstance operator*() const noexcept { return _inst; }

private:
  VkInstance _vk_instance() const {
    VkInstance inst;

    if (auto const res = vkCreateInstance(&_ci, nullptr, &inst); res != VK_SUCCESS)
      throw std::runtime_error("failed to create vulkan instance");

    return inst;
  }

  constexpr VkInstanceCreateInfo _vk_create_info() const noexcept {
    return VkInstanceCreateInfo{
      .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pNext                   = nullptr,
      .flags                   = 0,
      .pApplicationInfo        = &_ai,
      .enabledLayerCount       = 0,
      .ppEnabledLayerNames     = nullptr,
      .enabledExtensionCount   = 0,
      .ppEnabledExtensionNames = nullptr
    };
  }

  constexpr VkApplicationInfo _vk_app_info() const noexcept {
    return VkApplicationInfo{
      .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext              = nullptr,
      .pApplicationName   = nullptr,
      .applicationVersion = 0,
      .pEngineName        = nullptr,
      .engineVersion      = 0,
      .apiVersion         = 1 << 22 | 1 << 22
    };
  }
};

}
