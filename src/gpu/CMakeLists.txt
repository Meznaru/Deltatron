add_library("gpu")

find_package(Vulkan REQUIRED)

target_link_libraries(gpu
  PRIVATE
    cmake_metatarget
    util
    config_interface
    Vulkan::Vulkan)

target_include_directories(gpu
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")

target_sources(gpu
  PRIVATE
    "include/private/dt/gpu/vulkan/vulkan.hh"
    "include/private/dt/gpu/vulkan_instance.hh"
    "include/private/dt/gpu/vulkan_physical_devices.hh"

    "include/private/dt/gpu_imp.hh"

    "include/public/dt/gpu.hh"
    "src/dt/gpu.cc")

add_library("gpu_interface" INTERFACE)

target_include_directories(gpu_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
