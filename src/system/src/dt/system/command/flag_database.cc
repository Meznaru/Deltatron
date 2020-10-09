// flag_database.cc

#include <dt/system/command/flag_database.hh>

#include <dt/system/command/flag_id.hh>

#include <algorithm>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>

std::string dt::flag_database::gen_help_msg() const noexcept {
  std::stringstream hms{};

  int const name_maxlen = static_cast<int>(std::max_element(_db.begin(), _db.end(),
    [](auto const& large, auto const& next)
    { return large.second.name.size() < next.second.name.size(); }
      )->second.name.size() + 1);

  int const descr_maxlen = static_cast<int>(std::max_element(_db.begin(), _db.end(),
    [](auto const& large, auto const& next)
    { return large.second.description.size() < next.second.description.size(); }
      )->second.description.size());

  endl(hms);

  hms << std::left
    << std::setw(name_maxlen)  << "Flag Name"
    << std::setw(descr_maxlen) << "Description"
    << std::endl;

  for (auto const& p : _db)
    hms << std::left
      << std::setw(name_maxlen)  << p.second.name
      << std::setw(descr_maxlen) << p.second.description
      << std::endl;


  return hms.str();
} // gen_help_msg



std::map<dt::flag_id, dt::flag_database::_flag_info> dt::flag_database::_gen_flag_db() const noexcept {
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
        .description = "Sets the location the root directory resides in"
      }
    }
  };
} // _gen_flag_db
