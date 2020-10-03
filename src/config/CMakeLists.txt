# src directory CMake config

add_library("config" OBJECT)

target_include_directories(config
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")

target_sources(config
  PRIVATE
    "include/private/dt/config/filesystem.hh"

    "include/private/dt/config/command/flag_database.hh"
    "include/private/dt/config/command/arg_storage.hh"
    "include/private/dt/config/command/env_storage.hh"
    "include/private/dt/config/command.hh"

    "include/private/dt/config_imp.hh"

    "include/public/dt/config/filesystem/directory.hh"
    "include/public/dt/config/command/flag_id.hh"
    "include/public/dt/config/command/termflag_passed.hh"
    "include/public/dt/config.hh"
    "src/dt/config.cc")

target_link_libraries(config
  PRIVATE
    util
    cmake_metatarget)

add_library("config_interface" INTERFACE)

target_include_directories(config_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
