// filesystem.hh

#pragma once

#include <dt/system/filesystem/directory.hh>
#include <dt/system/command.hh>

#include <string>

namespace dt {

class filesystem final {
  std::string _root_dir;

public:
  filesystem(command const& cmd)
  : _root_dir(_eval_root_dir_path(cmd)) {}

  directory root_dir() const noexcept
  { return directory(_root_dir, nullptr); }

private:
  std::string _eval_root_dir_path(command const& c) const;
}; // class filesystem

} // namespace dt
