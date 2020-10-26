add_executable("deltatron")

target_link_libraries(deltatron
  PRIVATE
    cmake_metatarget
    system
    json)

target_include_directories(deltatron
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include/private")

target_sources(deltatron
  PRIVATE
    "include/private/dt/deltatron.hh"
    "src/dt/deltatron.cc"
    "src/dt/main.cc")
