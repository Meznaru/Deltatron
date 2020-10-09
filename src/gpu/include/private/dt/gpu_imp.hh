// gpu_imp.hh

#pragma once

#include <dt/gpu/vulkan_instance.hh>
#include <dt/gpu/vulkan_physical_devices.hh>

#include <dt/system.hh>

#include <dt/util/ignore.hh>

#include <iostream>

namespace dt {

class gpu_imp final {
  system               const& _system;
  vk_instance          const  _vkinst;
  vk_physical_devices  const  _vkpdevs;

public:
  gpu_imp(system const& sys)
  : _system(sys),
    _vkinst(),
    _vkpdevs(*_vkinst)
  {

    std::cout << "hello world\n";

    for (auto prop : _vkpdevs.properties_list())
      std::cout << _vkpdevs.device_detail_string(prop) << std::endl;
  }
};

}
