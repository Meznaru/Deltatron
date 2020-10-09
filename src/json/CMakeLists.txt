add_library("json")

target_include_directories(json
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")

target_link_libraries(json
  PRIVATE
    cmake_metatarget
    util)

target_sources(json
  PRIVATE
  "include/public/dt/json.hh"
  "include/private/dt/json_imp.hh"
  "src/dt/json.cc")

add_library("json_interface" INTERFACE)

target_include_directories(json_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
