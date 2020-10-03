// flag_database.hh

#pragma once

#include <dt/config/command/flag_id.hh>

#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

namespace dt {

class flag_database final {

  struct _flag_info final {
    std::string const name;
    std::string const description;
  };

  std::map<flag_id, _flag_info> const _db;

public:
  flag_database() noexcept
  : _db(_gen_flag_db()) {}

  char const* flag_name(dt::flag_id const id) const noexcept
  { return _db.at(id).name.c_str(); }

  bool is_flag(char const* v) const noexcept
  { return std::any_of(_db.begin(), _db.end(), [&v](auto const& e){ return e.second.name == v; }); }

  std::string gen_help_msg() const noexcept {
    std::stringstream hms{};

    int const name_maxlen = static_cast<int>(std::max_element(_db.begin(), _db.end(),
      [](auto const& large, auto const& next)
      { return large.second.name.size() < next.second.name.size(); })->second.name.size() + 1);

    int const descr_maxlen = static_cast<int>(std::max_element(_db.begin(), _db.end(),
      [](auto const& large, auto const& next)
      { return large.second.description.size() < next.second.description.size(); })->second.description.size());

    endl(hms);

    hms << std::left
      << std::setw(name_maxlen) << "Flag Name"
      << std::setw(descr_maxlen) << "Description"
      << std::endl;

    for (auto const& p : _db)
      hms << std::left
        << std::setw(name_maxlen) << p.second.name
        << std::setw(descr_maxlen) << p.second.description
        << std::endl;


    return hms.str();
  } // gen_help_msg

private:
  std::map<flag_id, _flag_info> _gen_flag_db() const noexcept {
    return
    {

      {
        flag_id::help,
        {
          .name        = "--help",
          .description = "Prints the help menu and exits"
        }
      },

      {
        flag_id::version,
        {
          .name        = "--version",
          .description = "Prints the program version and exits"
        }
      },
      {
        flag_id::build_info,
        {
          .name        = "--build-info",
          .description = "Prints the program compiler/platform and exits"
        }
      },
      {
        flag_id::root_directory_name,
        {
          .name        = "--root-directory-name",
          .description = "Sets the name of the root directory"
        }
      },

      {
        flag_id::root_directory_location,
        {
          .name        = "--root-directory-location",
          .description = "Sets the directory the root directory resides in"
        }
      }
    };
  } // _gen_flag_db
}; // class flag_database

}
