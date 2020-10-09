# src directory CMake system

add_library("system")

target_include_directories(system
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")

target_sources(system
  PRIVATE
    "include/public/dt/system/filesystem/directory.hh"
    "include/private/dt/system/filesystem.hh"
    "src/dt/system/filesystem.cc"

    "include/private/dt/system/command/flag_database.hh"
    "src/dt/system/command/flag_database.cc"

    "include/private/dt/system/command/arg_view.hh"
    "include/private/dt/system/command/env_view.hh"
    "include/private/dt/system/command.hh"

    "include/private/dt/system_imp.hh"

    "include/public/dt/system/command/flag_id.hh"
    "include/public/dt/system/command/termflag_passed.hh"
    "include/public/dt/system.hh"
    "src/dt/system.cc")

target_link_libraries(system
  PRIVATE
    util
    cmake_metatarget)

add_library("system_interface" INTERFACE)

target_include_directories(system_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
