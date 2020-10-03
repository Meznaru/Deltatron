// cmd.hh

#pragma once

#include <dt/config/command/flag_database.hh>
#include <dt/config/command/arg_storage.hh>
#include <dt/config/command/env_storage.hh>

#include <dt/config/command/flag_id.hh>
#include <dt/config/command/termflag_passed.hh>
#include <dt/cmake/project_info.hh>

#include <map>
#include <optional>
#include <string>

namespace dt {

class command final {
  dt::flag_database const _flag_db;
  dt::arg_storage   const _arg_store;
  dt::env_storage   const _env_store;

public:
  command(int const ac, char const** av, char const** ep)
  : _flag_db(),
    _arg_store(ac, av),
    _env_store(ep)
  { if (auto om{_termflag_passed()}; om) throw termflag_passed(om.value()); }

  bool cmdflag_passed(dt::flag_id id) const noexcept
  { return _arg_store.contains(_flag_db.flag_name(id)); }

  auto cmdflag_value(dt::flag_id id) const noexcept -> char const* {
    auto const val = _arg_store.arg_next_to(_flag_db.flag_name(id));
    return val && !_flag_db.is_flag(val) ? val : nullptr;
  }

  constexpr auto evar_defined(char const* var) const noexcept -> bool        { return _env_store.defined(var); }
  constexpr auto evar_value(char const* var)   const noexcept -> char const* { return _env_store.value(var);   }

private:
  std::optional<std::string> _termflag_passed() const noexcept {
    if (cmdflag_passed(dt::flag_id::help))
      return _flag_db.gen_help_msg();

    if (cmdflag_passed(dt::flag_id::version))
      return std::string(project::name) + " version " + project::version;

    if (cmdflag_passed(dt::flag_id::build_info))
      return std::string(project::compiler) + ' ' + project::os;

    return std::nullopt;
  }
}; // class command

} // namespace dt
