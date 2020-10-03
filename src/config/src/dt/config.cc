// config.cc

#include <dt/config.hh>
#include <dt/config_imp.hh>

#include <filesystem>
#include <fstream>
#include <string>

////////////
// config //
////////////////////////////////////////////////////////////////////

dt::config::config(int ac, char const** av, char const** ep)
: _config(std::make_unique<config_imp>(ac, av, ep)) {}

dt::config::~config() noexcept {}

bool dt::config::cmdflag_passed(dt::flag_id id) const noexcept
{ return _config->cmdflag_passed(id); }

char const* dt::config::cmdflag_value(dt::flag_id id) const noexcept
{ return _config->cmdflag_value(id); }

char const* dt::config::evar_value(char const* var) const noexcept
{ return _config->evar_value(var); }

bool dt::config::evar_defined(char const* var) const noexcept
{ return _config->evar_defined(var); }

dt::directory dt::config::rootdir() const noexcept
{ return _config->rootdir(); }

///////////////////
// dt::directory //
////////////////////////////////////////////////////////////////////

namespace dt {

fs::path _append_path(std::string const& base, char const* app) noexcept
{ fs::path p(base); return p /= app; }

}

dt::directory::directory(std::string const& path, directory const* parent) noexcept
: _parent(parent),
  _path(path) {}

dt::directory dt::directory::load_directory(char const* dname) const {
  using namespace ::std::string_literals;

  namespace fs = ::std::filesystem;

  fs::path p(_append_path(_path, dname));

  if (!fs::exists(p))
    fs::create_directory(p);

  else if (!fs::is_directory(p))
    throw std::runtime_error("error opening "s + dname + ": not a directory");

  return directory(p.string(), this);
}

std::string dt::directory::load_file(file_init file) const {
  auto       ifs    = std::ifstream(_append_path(_path, file.name), std::ios::binary | std::ios::ate);
  auto const ifs_sz = ifs.tellg();

  if (ifs_sz < 0) {
    write_file(file);
    return load_file(file);
  }

  auto str = std::string(static_cast<std::string::size_type>(ifs_sz), 0);

  ifs.seekg(0);
  ifs.read(str.data(), ifs_sz);

  return str;
}

void dt::directory::write_file(file_init file) const {
  std::ofstream ofs(_append_path(_path, file.name), std::ios::binary | std::ios::trunc);

  if (file.data) {
    ofs.write(file.data, static_cast<std::streamsize>(file.size ? file.size : std::strlen(file.data)));

  } else {
    ofs.write(file.data, 0); // win32 platform hangs for ~2 seconds when passing nullptr for std::strlen()
  }
}

dt::directory const* dt::directory::parent() const noexcept
{ return _parent ? _parent : nullptr; }
