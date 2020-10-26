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

  auto cmdflag_passed(dt::flag_id id)     const noexcept -> bool;
  auto cmdflag_value(dt::flag_id id)      const noexcept -> std::optional<std::string_view>;
  auto evar_defined(std::string_view var) const noexcept -> bool;
  auto evar_value(std::string_view var)   const noexcept -> std::optional<std::string_view>;
  auto rootdir()                          const noexcept -> directory;

  system(system&)  = delete;
  system(system&&) = delete;

  system operator=(system)    = delete;
  system& operator=(system&&) = delete;
}; // class system

} // namespace dt
