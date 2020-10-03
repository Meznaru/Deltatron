add_library("util" INTERFACE)

target_sources(util
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/dt/util/system.hh")

target_include_directories(util
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
