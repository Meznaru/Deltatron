// os_imp.hh

#pragma once

#include <dt/system/os/os_id.hh>

namespace dt {

class os final {
static constexpr os_id _id{
  #if defined _WIN32
    os_id::windows
  #elif __APPLE__ && __MACH__
    os_id::macos
  #elif defined __gnu_linux__
    os_id::linux
  #else
    os_id::unix
  #endif
};

public:
  static constexpr os_id get_id() noexcept { return _id; }

  static constexpr bool is_windows() noexcept { return _id == os_id::windows; }
};

}
