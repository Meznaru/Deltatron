// filesystem.hh

#pragma once

#include <dt/system/filesystem/directory.hh>
#include <dt/system/command.hh>

#include <string>

namespace dt {

class filesystem final {
  std::string _rootdir;

public:
  filesystem(command const& cmd)
  : _rootdir(_eval_root_dir_path(cmd)) {}

  directory rootdir() const noexcept
  { return directory(_rootdir, nullptr); }

private:
  std::string _eval_root_dir_path(command const& c) const;
}; // class filesystem

} // namespace dt
