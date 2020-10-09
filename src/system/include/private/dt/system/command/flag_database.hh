// flag_database.hh

#pragma once

#include <dt/system/command/flag_id.hh>

#include <algorithm>
#include <map>
#include <string>

namespace dt {

class flag_database final {

  struct _flag_info final {
    std::string name;
    std::string description;
  };

  std::map<flag_id, _flag_info> _db;

public:
  flag_database() noexcept
  : _db(_gen_flag_db()) {}

  char const* flag_name(dt::flag_id const id) const noexcept
  { return _db.at(id).name.c_str(); }

  bool is_flag(std::string_view v) const noexcept
  { return std::any_of(_db.begin(), _db.end(), [&v](auto const& f){ return f.second.name == v; }); }

  std::string gen_help_msg() const noexcept;

private:
  std::map<flag_id, _flag_info> _gen_flag_db() const noexcept;
}; // class flag_database

}
