// config_imp.hh

#pragma once

#include <dt/config/command.hh>
#include <dt/config/filesystem.hh>

namespace dt {

class config_imp final {
  dt::command    const _cmd;
  dt::filesystem const _fs;

public:
  config_imp(int const ac, char const** av, char const** ep)
: _cmd(ac, av, ep),
  _fs(_cmd) {}

  bool cmdflag_passed(dt::flag_id const id) const noexcept
  { return _cmd.cmdflag_passed(id); }

  char const* cmdflag_value(dt::flag_id const id) const noexcept
  { return _cmd.cmdflag_value(id); }

  char const* evar_value(char const* var) const noexcept
  { return _cmd.evar_value(var); }

  bool evar_defined(char const* var) const noexcept
  { return _cmd.evar_defined(var); }

  directory rootdir() const noexcept
  { return _fs.rootdir(); }
}; // class config

} // namespace dt
