// filesystem.cc

#include <dt/system/filesystem/directory.hh>
#include <dt/system/filesystem.hh>

#include <dt/system/os.hh>

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <string_view>

namespace dt {

namespace fs = ::std::filesystem;

}

std::string dt::filesystem::_eval_root_dir_path(command const& c) const {
  fs::path root{};

  // Determine root directory location
  if (auto const opt_custom_dir = c.cmdflag_value(flag_id::root_directory_location); opt_custom_dir)
    root /= opt_custom_dir.value();

  else if (auto const opt_appdata = c.evar_value("LOCALAPPDATA"); opt_appdata && os::is_windows())
    (root /= opt_appdata.value()) /= "Programs";

  else if (auto const opt_home_dir = c.evar_value("HOME"); opt_home_dir)
    root /= opt_home_dir.value();

  // Determine root directory name
  if (auto const opt_custom_name = c.cmdflag_value(flag_id::root_directory_name); opt_custom_name)
    root /= opt_custom_name.value();

  else if (os::is_windows())
    root /= "Deltatron";

  else
    root /= ".deltatron";

  fs::create_directories(root);

  return root.string();
} // _eval_root_dir_path

dt::directory::directory(std::string const& path, directory const* parent) noexcept
: _path(path),
  _parent(parent) {}

std::optional<dt::directory> dt::directory::parent() const noexcept {
  if (_parent)
    return *_parent;

  return std::nullopt;
}

std::string dt::directory::name() const noexcept
{ return _parent ? fs::path(_path).filename().string() : "root"; }

dt::directory dt::directory::mkdir(std::string const& name) const {
  fs::path p(fs::path(_path) / name);

  if (!fs::exists(p))
    fs::create_directory(p);

  else if (!fs::is_directory(p))
    throw std::runtime_error(name + ": not a directory");

  return *this;
}

dt::directory dt::directory::chdir(std::string const& name) const {
  fs::path p(fs::path(_path) / name);

  if (!fs::exists(p))
    fs::create_directory(p);

  else if (!fs::is_directory(p))
    throw std::runtime_error(name + ": not a directory");

  return directory(p.string(), this);
}

std::optional<std::string> dt::directory::fload(std::string const& name) const {
  if (std::ifstream ifs(fs::path(_path) / name, std::ios::binary | std::ios::ate); ifs.is_open()) {
    std::string fdata(std::string::size_type(ifs.tellg()), 0);
    return std::move((ifs.seekg(0), ifs.read(fdata.data(), std::streamsize(fdata.size())), fdata));
  } return std::nullopt;
}

void dt::directory::fwrite(std::string const& name, std::string_view data) const
{ std::ofstream(fs::path(_path) / name, std::ios::binary | std::ios::trunc).write(data.data(), std::streamsize(data.size())); }
