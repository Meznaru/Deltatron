add_library("json")

target_include_directories(json
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private"
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")

target_link_libraries(json
  PRIVATE
    cmake_metatarget)

target_sources(json
  PRIVATE
    "include/private/dt/json/container/value.hh"
    "include/public/dt/json/container/type.hh"
    "include/public/dt/json/container.hh"
    "include/private/dt/json/container_imp.hh"
    "include/private/dt/json/parser/lexer.hh"
    "include/private/dt/json/parser/semantic_analysis.hh"
    "include/private/dt/json/parser.hh"
    "include/private/dt/json_imp.hh"
    "include/public/dt/json.hh"
    "src/dt/json.cc")

add_library("json_interface" INTERFACE)

target_include_directories(json_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
