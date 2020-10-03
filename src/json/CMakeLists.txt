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
  "include/private/dt/json/token_stream/token.hh"

  "include/private/dt/json/token_stream/verify_stream.hh"
  "include/private/dt/json/token_stream/stream_lexer.hh"
  "include/private/dt/json/token_stream.hh"
  "src/dt/json/token_stream.cc"

  "include/private/dt/json_imp.hh"
  "include/public/dt/json.hh"
  "src/dt/json.cc")

add_library("json_interface" INTERFACE)

target_include_directories(json_interface
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/public")
