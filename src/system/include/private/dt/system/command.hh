// cmd.hh

#pragma once

#include <dt/system/command/flag_database.hh>
#include <dt/system/command/arg_view.hh>
#include <dt/system/command/env_view.hh>

#include <dt/system/command/flag_id.hh>
#include <dt/system/command/termflag_passed.hh>
#include <dt/cmake/project_info.hh>

#include <map>
#include <optional>
#include <string>

namespace dt {

class command final {
  flag_database _flag_db;
  arg_view      _arg_view;
  env_view      _env_view;

public:
  command(int const ac, char const** av, char const** ep)
  : _flag_db(),
    _arg_view(ac, av),
    _env_view(ep)
  {
    if (auto opt_msg{_termflag_passed()}; opt_msg)
      throw termflag_passed(opt_msg.value());
  }

  bool cmdflag_passed(dt::flag_id id) const noexcept
  { return _arg_view.contains(_flag_db.flag_name(id)); }

  std::optional<std::string_view> cmdflag_value(dt::flag_id id) const noexcept {
    if (auto opt_val{_arg_view.arg_next_to(_flag_db.flag_name(id))}; opt_val && !_flag_db.is_flag(opt_val.value()))
      return opt_val;

    return std::nullopt;
  }

  constexpr bool evar_defined(std::string_view var) const noexcept
  { return _env_view.defined(var); }

  constexpr std::optional<std::string_view> evar_value(std::string_view var) const noexcept
  { return _env_view.value(var); }

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
