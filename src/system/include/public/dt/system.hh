// system.hh

#pragma once

#include <dt/system/command/flag_id.hh>
#include <dt/system/command/termflag_passed.hh>

#include <dt/system/filesystem/directory.hh>

#include <memory>
#include <optional>
#include <string_view>

namespace dt {

class system_imp;

class system final {
  std::unique_ptr<system_imp> _system;

public:
  system(int argc, char const** argv, char const** envp);

  ~system() noexcept;

  bool cmdflag_passed(dt::flag_id id) const noexcept;

  std::optional<std::string_view> cmdflag_value(dt::flag_id id) const noexcept;

  bool evar_defined(char const* var) const noexcept;

  std::optional<std::string_view> evar_value(char const* var) const noexcept;

  directory rootdir() const noexcept;

  system(system&)  = delete;
  system(system&&) = delete;

  system operator=(system)    = delete;
  system& operator=(system&&) = delete;
}; // class system

} // namespace dt
