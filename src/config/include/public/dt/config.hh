// config.hh

#pragma once

#include <dt/config/command/flag_id.hh>
#include <dt/config/command/termflag_passed.hh>

#include <dt/config/filesystem/directory.hh>

#include <memory>
#include <string>

namespace dt {

class config_imp;

class config final {
  std::unique_ptr<config_imp> const _config;

public:
  config(int argc, char const** argv, char const** envp);

  ~config() noexcept;

  bool cmdflag_passed(dt::flag_id id) const noexcept;

  char const* cmdflag_value(dt::flag_id id) const noexcept;

  char const* evar_value(char const* var) const noexcept;

  bool evar_defined(char const* var) const noexcept;

  directory rootdir() const noexcept;
}; // class config

} // namespace dt
