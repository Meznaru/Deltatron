// filesystem.hh

#pragma once

#include <dt/config/filesystem/directory.hh>
#include <dt/config/command.hh>
#include <dt/util/system.hh>

#include <filesystem>
#include <string>

namespace dt {

namespace fs = ::std::filesystem;

class filesystem final {
  std::string const _rootdir;

public:
  filesystem(command const& cmd) noexcept
  : _rootdir(_eval_root_dir_path(cmd)) {}

  directory rootdir() const noexcept
  { return directory(_rootdir, nullptr); }

private:
  std::string _eval_root_dir_path(command const& c) noexcept {
    fs::path rdp{};

    if (auto const custom_dir = c.cmdflag_value(flag_id::root_directory_location); custom_dir) {
      rdp /= custom_dir;

    } else if (system_os == os::windows) {
      if (auto const appdata = c.evar_value("LOCALAPPDATA"); appdata) {
        rdp /= appdata;
        rdp /= "Programs";
      }

    } else if (auto const userdir = c.evar_value("USER"); userdir) {
        rdp /= userdir;

    }

    if (auto const custom_name = c.cmdflag_value(flag_id::root_directory_name); custom_name) {
      rdp /= custom_name;

    } else if (system_os == os::windows) {
      rdp /= "Deltatron";

    } else {
      rdp /= ".deltatron";

    }
    
    fs::create_directories(rdp);

    return rdp.string();
  } // _eval_root_dir_path
}; // class filesystem

} // namespace dt
