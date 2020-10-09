// system_imp.hh

#pragma once

#include <dt/system/command.hh>
#include <dt/system/filesystem.hh>

namespace dt {

class system_imp final {
  dt::command    _cmd;
  dt::filesystem _fs;

public:
  system_imp(int const ac, char const** av, char const** ep)
  : _cmd(ac, av, ep),
    _fs(_cmd) {}

  bool cmdflag_passed(dt::flag_id const id) const noexcept { return _cmd.cmdflag_passed(id); }
  auto cmdflag_value(dt::flag_id const id)  const noexcept { return _cmd.cmdflag_value(id);  }
  bool evar_defined(char const* var)        const noexcept { return _cmd.evar_defined(var);  }
  auto evar_value(char const* var)          const noexcept { return _cmd.evar_value(var);    }

  auto rootdir() const noexcept { return _fs.rootdir(); }
}; // class system_imp

} // namespace dt
