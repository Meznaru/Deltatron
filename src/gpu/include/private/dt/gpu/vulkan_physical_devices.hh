// vulkan_devices.hh

#pragma once

#include <dt/gpu/vulkan/vulkan.hh>

#include <sstream>
#include <string>
#include <vector>

namespace dt {

class vk_physical_devices final {
public:
  using pdevs_t      = std::vector<VkPhysicalDevice>;
  using pdevprops_t  = std::vector<VkPhysicalDeviceProperties>;
  using pdevprops2_t = std::vector<VkPhysicalDeviceProperties2>;

private:
  vksize_t     const  _size;
  pdevs_t      const  _pdevs;
  pdevprops_t  const  _pdevprops;
  pdevprops2_t const  _pdevprops2;

public:
  vk_physical_devices(VkInstance const& inst)
  : _size(_get_pdev_size(inst)),
    _pdevs(_get_pdevs(inst)),
    _pdevprops(_get_pdevprops()),
    _pdevprops2(_get_pdevprops2()) {}

  std::string device_detail_string(VkPhysicalDeviceProperties const& pdevprop) const noexcept {
    std::stringstream pds{};

    pds << "Physical Device '" << pdevprop.deviceName << "'" << std::endl;
    pds << "Vulkan API version: " << pdevprop.apiVersion << std::endl;

    return pds.str();
  }

  pdevprops_t const& properties_list() const noexcept { return _pdevprops; }

private:
  vksize_t _get_pdev_size(VkInstance const& inst) const noexcept {
    vksize_t size;

    vkEnumeratePhysicalDevices(inst, &size, nullptr);

    return size;
  }

  pdevs_t _get_pdevs(VkInstance const& inst) const noexcept {
    pdevs_t pdevs(_size);

    auto s = _size;
    vkEnumeratePhysicalDevices(inst, &s, pdevs.data());

    return pdevs;
  }

  pdevprops_t _get_pdevprops() const noexcept {
    pdevprops_t pdevprops(_size);

    for (vksize_t i{}; i < _size; ++i)
      vkGetPhysicalDeviceProperties(_pdevs[i], pdevprops.data() + i);

    return pdevprops;
  }

  pdevprops2_t _get_pdevprops2() const noexcept {
    pdevprops2_t pdevprops2(_size);

    for (vksize_t i{}; i < _size; ++i)
      vkGetPhysicalDeviceProperties2(_pdevs[i], pdevprops2.data() + i);

    return pdevprops2;
  }

};

}
