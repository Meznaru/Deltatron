// system.hh

#pragma once

namespace dt {

enum class os {
  windows, macos,
  linux, unix
};

constexpr os const system_os {
#if defined _WIN32
  os::windows
#elif __APPLE__ && __MACH__
  os::macos
#elif defined __gnu_linux__
  os::linux
#else
  os::unix
#endif
};

} // namespace dt
