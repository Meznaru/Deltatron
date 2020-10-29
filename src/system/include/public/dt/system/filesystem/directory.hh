// directory.hh

#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace dt {

class file;

class filesystem;

class directory final {
  std::string      _path;
  directory const* _parent;

  friend class ::dt::filesystem;

public:
  auto parent() const noexcept -> std::optional<directory>;
  auto name()   const noexcept -> std::string;

  auto chdir(std::string const& name) const -> directory;
  auto mkdir(std::string const& name) const -> directory;

  auto fload(std::string const& name)                                const -> std::optional<file>;
  auto fload(std::string const& name, std::string_view default_data) const -> file;
  auto fwrite(std::string const& name, std::string_view data)        const -> void;

private:
  directory(std::string const& path, directory const* parent) noexcept;
};

class file final {
  std::string _name;
  std::string _data;

  friend class ::dt::directory;

  file(std::string const& name, std::string const& data)
  : _name(name),
    _data(data) {}

public:
  constexpr auto name() const noexcept -> std::string const& { return _name; }
  constexpr auto data() const noexcept -> std::string const& { return _data; }
};

}
